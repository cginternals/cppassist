
#include <cppassist/cmdline/CommandLineAction.h>

#include <cppassist/string/manipulation.h>
#include <cppassist/cmdline/CommandLineCommand.h>
#include <cppassist/cmdline/CommandLineOption.h>
#include <cppassist/cmdline/CommandLineSwitch.h>
#include <cppassist/cmdline/CommandLineParameter.h>


namespace cppassist
{


CommandLineAction::CommandLineAction(const std::string & name, const std::string & description)
: m_name(name)
, m_description(description)
, m_optionalParametersAllowed(false)
, m_optionalParameterName("arg")
, m_activated(false)
{
}

CommandLineAction::~CommandLineAction()
{
}

const std::string & CommandLineAction::name() const
{
    return m_name;
}

void CommandLineAction::setName(const std::string & name)
{
    m_name = name;
}

const std::string & CommandLineAction::description() const
{
    return m_description;
}

void CommandLineAction::setDescription(const std::string & description)
{
    m_description = description;
}

const std::vector<CommandLineCommand *> & CommandLineAction::commands() const
{
    return m_commands;
}

CommandLineCommand * CommandLineAction::getCommand(const std::string & name) const
{
    for (auto * command : m_commands)
    {
        if (command->name() == name)
        {
            return command;
        }
    }

    return nullptr;
}

void CommandLineAction::add(CommandLineCommand * command)
{
    m_commands.push_back(command);
}

const std::vector<CommandLineOption *> & CommandLineAction::options() const
{
    return m_options;
}

CommandLineOption * CommandLineAction::getOption(const std::string & name) const
{
    for (auto * option : m_options)
    {
        if (option->shortName() == name || option->longName() == name)
        {
            return option;
        }
    }

    return nullptr;
}

void CommandLineAction::add(CommandLineOption * option)
{
    m_options.push_back(option);
}

const std::vector<CommandLineSwitch *> & CommandLineAction::switches() const
{
    return m_switches;
}

CommandLineSwitch * CommandLineAction::getSwitch(const std::string & name) const
{
    for (auto * sw : m_switches)
    {
        if (sw->shortName() == name || sw->longName() == name)
        {
            return sw;
        }
    }

    return nullptr;
}

void CommandLineAction::add(CommandLineSwitch * sw)
{
    m_switches.push_back(sw);
}

const std::vector<CommandLineParameter *> & CommandLineAction::parameters() const
{
    return m_parameters;
}

CommandLineParameter * CommandLineAction::getParameter(const std::string & name) const
{
    for (auto * parameter : m_parameters)
    {
        if (parameter->name() == name)
        {
            return parameter;
        }
    }

    return nullptr;
}

CommandLineParameter * CommandLineAction::getParameter(size_t index) const
{
    if (index < m_parameters.size())
    {
        return m_parameters[index];
    }

    return nullptr;
}

bool CommandLineAction::optionalParametersAllowed() const
{
    return m_optionalParametersAllowed;
}

void CommandLineAction::setOptionalParametersAllowed(bool allowed)
{
    m_optionalParametersAllowed = allowed;
}

const std::string & CommandLineAction::optionalParameterName() const
{
    return m_optionalParameterName;
}

void CommandLineAction::setOptionalParameterName(const std::string & name)
{
    m_optionalParameterName = name;
}

void CommandLineAction::add(CommandLineParameter * parameter)
{
    m_parameters.push_back(parameter);
}

std::string CommandLineAction::usage() const
{
    std::string usage;

    for (auto * command : m_commands)
    {
        if (usage.size() > 0) usage += " ";

        usage += command->name();
    }

    for (auto * sw : m_switches)
    {
        if (usage.size() > 0) usage += " ";
        if (sw->isOptional()) usage += "[";
        usage += sw->name();
        if (sw->isOptional()) usage += "]";
    }

    for (auto * option : m_options)
    {
        if (usage.size() > 0) usage += " ";
        if (option->isOptional()) usage += "[";
        usage += option->name() + " <" + option->valueName() + ">";
        if (option->isOptional()) usage += "]";
    }

    for (auto * param : m_parameters)
    {
        if (usage.size() > 0) usage += " ";
        if (param->isOptional()) usage += "[";
        usage += "<" + param->name() + ">";
        if (param->isOptional()) usage += "]";
    }

    if (m_optionalParametersAllowed)
    {
        if (usage.size() > 0) usage += " ";
        usage += "[<" + m_optionalParameterName + ">]*";
    }

    return usage;
}

void CommandLineAction::reset()
{
    m_activated = false;

    m_optionalParameters.clear();
    m_errors.clear();

    for (auto * command : m_commands)
    {
        command->setActivated(false);
    }

    for (auto * sw : m_switches)
    {
        sw->setActivated(false);
        sw->setCount(0);
    }

    for (auto * option : m_options)
    {
        option->setValue("");
    }

    for (auto * parameter : m_parameters)
    {
        parameter->setValue("");
    }
}

void CommandLineAction::parse(int argc, char * argv[])
{
    std::vector<std::string> args;

    // Reset internal state
    reset();

    // List arguments
    for (int i=1; i<argc; i++)
    {
        std::string arg = argv[i];

        // Expand grouped options (e.g., "-abc" -> "-a -b -c")
        if (!string::hasPrefix(arg, "--") && string::hasPrefix(arg, "-") && arg.size() > 2)
        {
            for (size_t j=0; j<arg.size()-1; j++)
            {
                std::string opt = std::string("-") + arg[j+1];
                args.push_back(opt);
            }
        }
        else
        {
            args.push_back(arg);
        }
    }

    // Parse command line
    size_t numParameters = 0;
    for (size_t i=0; i<args.size(); i++)
    {
        // Get current and next argument
        std::string arg  = args[i];
        std::string next = (i+1 < args.size() ? args[i+1] : "");

        // If item starts with "--" or "-", it may be an option or a switch
        if (string::hasPrefix(arg, "-"))
        {
            CommandLineOption * option = getOption(arg);
            CommandLineSwitch * sw     = getSwitch(arg);

            // Option
            if (option)
            {
                // Check that next item is a valid value (and not empty or an option)
                if (!next.empty() && !string::hasPrefix(next, "-"))
                {
                    option->setValue(next);
                    i++;
                }
                else
                {
                    // Error: Value expected
                    m_errors.push_back("Expected value for '" + arg + "'");
                }
            }

            // Switch
            else if (sw)
            {
                sw->setActivated(true);
                sw->setCount(sw->count() + 1);
            }

            // Error: Unknown option
            else
            {
                m_errors.push_back("Unknown option '" + arg + "'");
            }
        }

        // Otherwise, it may be a command or a parameter
        else
        {
            CommandLineCommand * command = getCommand(arg);

            // Command
            if (command)
            {
                command->setActivated(true);
            }

            // Parameter
            else
            {
                auto * parameter = getParameter(numParameters);

                // Parameter found
                if (parameter)
                {
                    parameter->setValue(arg);
                    numParameters++;
                }

                // Unknown parameter
                else
                {
                    m_optionalParameters.push_back(arg);
                }
            }
        }
    }

    // Check if this action is activated
    m_activated = checkActivated();

    // Check for errors
    checkErrors();
}

bool CommandLineAction::hasErrors() const
{
    return m_errors.size() > 0;
}

const std::vector<std::string> & CommandLineAction::errors() const
{
    return m_errors;
}

bool CommandLineAction::activated() const
{
    return m_activated;
}

const std::vector<std::string> & CommandLineAction::optionalParameters() const
{
    return m_optionalParameters;
}

int CommandLineAction::execute()
{
    // To be implement in derived classes
    return 0;
}

bool CommandLineAction::checkActivated()
{
    // Check if this action has been activated
    for (auto * command : m_commands)
    {
        if (!command->activated())
        {
            return false;
        }
    }

    for (auto * sw : m_switches)
    {
        if (sw->optional() == CommandLineSwitch::NonOptional && !sw->activated())
        {
            return false;
        }
    }

    for (auto * option : m_options)
    {
        if (option->optional() == CommandLineOption::NonOptional && option->value().empty())
        {
            return false;
        }
    }

    return true;
}

void CommandLineAction::checkErrors()
{
    // Look for options that miss a value
    for (auto * option : m_options)
    {
        if (option->optional() == CommandLineOption::NonOptional && option->value().empty())
        {
            m_errors.push_back("Expected value for '" + option->name() + "'");
        }
    }

    // Look for parameters that have not been specified
    for (auto * parameter : m_parameters)
    {
        if (parameter->optional() == CommandLineParameter::NonOptional && parameter->value().empty())
        {
            m_errors.push_back("Expected <" + parameter->name() + ">");
        }
    }

    // Look for unrecognized parameters
    if (!m_optionalParametersAllowed)
    {
        for (auto parameter : m_optionalParameters)
        {
            m_errors.push_back("Unknown parameter '" + parameter + "'");
        }
    }
}


} // namespace cppassist
