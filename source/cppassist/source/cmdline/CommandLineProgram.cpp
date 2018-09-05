
#include <cppassist/cmdline/CommandLineProgram.h>

#include <set>

#include <cppassist/logging/logging.h>
#include <cppassist/string/manipulation.h>
#include <cppassist/cmdline/CommandLineProgram.h>
#include <cppassist/cmdline/CommandLineCommand.h>
#include <cppassist/cmdline/CommandLineOption.h>
#include <cppassist/cmdline/CommandLineParameter.h>
#include <cppassist/cmdline/CommandLineSwitch.h>


namespace cppassist
{


CommandLineProgram::CommandLineProgram(const std::string & name, const std::string & shortDesc, const std::string & description)
: m_name(name)
, m_shortDesc(shortDesc)
, m_description(description)
, m_selectedAction(nullptr)
, m_optionalParametersAllowed(false)
, m_optionalParameterName("arg")
, m_activated(false)
{
}

CommandLineProgram::~CommandLineProgram()
{
}

const std::string & CommandLineProgram::name() const
{
    return m_name;
}

void CommandLineProgram::setName(const std::string & name)
{
    m_name = name;
}

const std::string & CommandLineProgram::shortDesc() const
{
    return m_shortDesc;
}

void CommandLineProgram::setShortDesc(const std::string & shortDesc)
{
    m_shortDesc = shortDesc;
}

const std::string & CommandLineProgram::description() const
{
    return m_description;
}

void CommandLineProgram::setDescription(const std::string & description)
{
    m_description = description;
}

const std::vector<CommandLineProgram *> & CommandLineProgram::actions() const
{
    return m_actions;
}

CommandLineProgram * CommandLineProgram::getAction(const std::string & name) const
{
    for (auto * action : m_actions)
    {
        if (action->name() == name)
        {
            return action;
        }
    }

    return nullptr;
}

void CommandLineProgram::add(CommandLineProgram * action)
{
    m_actions.push_back(action);
}

const std::vector<CommandLineCommand *> & CommandLineProgram::commands() const
{
    return m_commands;
}

CommandLineCommand * CommandLineProgram::getCommand(const std::string & name) const
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

void CommandLineProgram::add(CommandLineCommand * command)
{
    m_commands.push_back(command);
}

const std::vector<CommandLineOption *> & CommandLineProgram::options() const
{
    return m_options;
}

CommandLineOption * CommandLineProgram::getOption(const std::string & name) const
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

void CommandLineProgram::add(CommandLineOption * option)
{
    m_options.push_back(option);
}

const std::vector<CommandLineSwitch *> & CommandLineProgram::switches() const
{
    return m_switches;
}

CommandLineSwitch * CommandLineProgram::getSwitch(const std::string & name) const
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

void CommandLineProgram::add(CommandLineSwitch * sw)
{
    m_switches.push_back(sw);
}

const std::vector<CommandLineParameter *> & CommandLineProgram::parameters() const
{
    return m_parameters;
}

CommandLineParameter * CommandLineProgram::getParameter(const std::string & name) const
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

CommandLineParameter * CommandLineProgram::getParameter(size_t index) const
{
    if (index < m_parameters.size())
    {
        return m_parameters[index];
    }

    return nullptr;
}

bool CommandLineProgram::optionalParametersAllowed() const
{
    return m_optionalParametersAllowed;
}

void CommandLineProgram::setOptionalParametersAllowed(bool allowed)
{
    m_optionalParametersAllowed = allowed;
}

const std::string & CommandLineProgram::optionalParameterName() const
{
    return m_optionalParameterName;
}

void CommandLineProgram::setOptionalParameterName(const std::string & name)
{
    m_optionalParameterName = name;
}

void CommandLineProgram::add(CommandLineParameter * parameter)
{
    m_parameters.push_back(parameter);
}

std::string CommandLineProgram::usage() const
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

std::string CommandLineProgram::help(CommandLineProgram * forAction) const
{
    std::string msg = "";

    // Show help for one action or all?
    if (forAction == nullptr)
    {
        // For all actions ...

        // Add short description
        if (!m_shortDesc.empty())
        {
            msg += m_shortDesc + "\n";
            msg += "\n";
        }

        // Add description
        if (!m_description.empty())
        {
            msg += m_description + "\n";
            msg += "\n";
        }
    } else {
        // For a specific action ...

        if (!forAction->description().empty())
        {
            msg += forAction->description() + "\n";
            msg += "\n";
        }
    }

    // Choose action(s) to display
    std::vector<CommandLineProgram *> actions;
    if (forAction) actions.push_back(forAction);
    else           actions = m_actions;

    // Display usage texts
    bool first = true;

    for (auto * action : actions)
    {
        msg += (first ? "usage: " : "  or   ") + m_name + " " + action->usage() + "\n";
        first = false;
    }

    msg += "\n";

    // Collect all options and switches to calculate the maximum string length
    std::set<CommandLineOption *> options;
    std::set<CommandLineSwitch *> switches;
    size_t length = 0;

    for (auto * action : actions)
    {
        for (auto * sw : action->switches())
        {
            if (!switches.insert(sw).second)
                continue;

            length = std::max(sw->names().size(), length);
        }

        for (auto * option : action->options())
        {
            if (!options.insert(option).second)
                continue;

            length = std::max(option->names().size(), length);
        }
    }

    // Display options
    msg += "Options:\n";

    for (auto * sw : switches)
    {
        msg += " " + string::padRight(sw->names(), length) + "  " + sw->description() + "\n";
    }

    for (auto * option : options)
    {
        msg += " " + string::padRight(option->names(), length) + "  " + option->description() + "\n";
    }

    // Return help text
    return msg;
}

void CommandLineProgram::print(const std::string & msg)
{
    cppassist::info() << msg;
}

void CommandLineProgram::reset()
{
    for (auto * action : m_actions)
    {
        action->reset();
    }

    m_selectedAction = nullptr;

    m_activated = false;

    m_unknownArgs.clear();
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

int CommandLineProgram::execute(int argc, char * argv[])
{
    // Parse command line
    parse(argc, argv);

    // Check if a valid action has been selected
    if (!hasErrors())
    {
        // Execute action
        return execute();
    }

    // Print help
    print(help(selectedAction()));

    // Print errors
    if (hasErrors())
    {
        // Print error message
        std::string error = errors()[0];
        print("Error: " + error);

        // Indicate error condition
        return 1;
    }

    // Return without error
    return 0;
}

int CommandLineProgram::executeAction(CommandLineProgram * action)
{
    if (action)
    {
        return action->execute();
    }

    return 0;
}

void CommandLineProgram::parse(int argc, char * argv[])
{
    // Set program name if not set before
    if (m_name.empty()) {
        m_name = argv[0];
    }

    // List arguments
    std::vector<std::string> args;

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
    tryParse(args);

    // Check if this action is activated
    m_activated = checkActivated();
}

bool CommandLineProgram::hasErrors() const
{
    if (m_selectedAction)
    {
        return m_selectedAction->hasErrors();
    }

    return m_errors.size() > 0;
}

const std::vector<std::string> & CommandLineProgram::errors() const
{
    if (m_selectedAction)
    {
        return m_selectedAction->errors();
    }

    return m_errors;
}

bool CommandLineProgram::activated() const
{
    return m_activated;
}

const std::vector<std::string> & CommandLineProgram::unknownArguments() const
{
    if (m_selectedAction)
    {
        return m_selectedAction->unknownArguments();
    }

    return m_unknownArgs;
}

int CommandLineProgram::execute()
{
    // To be implement in derived classes

    if (m_selectedAction)
    {
        return m_selectedAction->execute();
    }

    return 0;
}

bool CommandLineProgram::tryParse(std::vector<std::string> & args)
{
    // Reset status
    reset();

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
                m_unknownArgs.push_back(arg);
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
                    m_unknownArgs.push_back(arg);
                }
            }
        }
    }

    for (auto action : m_actions)
    {
        if (action->tryParse(m_unknownArgs))
        {
            m_selectedAction = action;
            break;
        }
    }

    checkErrors();

    m_activated = checkActivated();

    return m_activated;
}

bool CommandLineProgram::checkActivated()
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

void CommandLineProgram::checkErrors()
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

    // Look for commands that have not been activated
    for (auto * command : m_commands)
    {
        if (!command->activated())
        {
            m_errors.push_back("Expected '" + command->name() + "'");
        }
    }

    // Look for required switches that have not been activated
    for (auto * cmdSwitch : m_switches)
    {
        if (cmdSwitch->optional() == CommandLineSwitch::NonOptional && !cmdSwitch->activated())
        {
            m_errors.push_back("Expected '" + cmdSwitch->name() + "'");
        }
    }

    // Look for unrecognized parameters
    if (!m_optionalParametersAllowed)
    {
        for (auto parameter : unknownArguments())
        {
            m_errors.push_back("Unknown argument '" + parameter + "'");
        }
    }

    // Check if action was selected
    if (!m_actions.empty() && !m_selectedAction)
    {
        m_errors.push_back("No action selected");
    }
}

CommandLineProgram * CommandLineProgram::selectedAction() const
{
    return m_selectedAction;
}


} // namespace cppassist
