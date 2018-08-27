
#include <cppassist/cmdline/CommandLineProgram.h>

#include <set>

#include <cppassist/logging/logging.h>
#include <cppassist/string/manipulation.h>
#include <cppassist/cmdline/CommandLineAction.h>
#include <cppassist/cmdline/CommandLineOption.h>
#include <cppassist/cmdline/CommandLineSwitch.h>


namespace cppassist
{


CommandLineProgram::CommandLineProgram(const std::string & name, const std::string & shortDesc, const std::string & description)
: m_name(name)
, m_shortDesc(shortDesc)
, m_description(description)
, m_selectedAction(nullptr)
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

const std::vector<CommandLineAction *> & CommandLineProgram::actions() const
{
    return m_actions;
}

CommandLineAction * CommandLineProgram::getAction(const std::string & name) const
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

void CommandLineProgram::add(CommandLineAction * action)
{
    m_actions.push_back(action);
}

std::string CommandLineProgram::help(CommandLineAction * forAction) const
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
    std::vector<CommandLineAction *> actions;
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
}

int CommandLineProgram::execute(int argc, char * argv[])
{
    // Parse command line
    parse(argc, argv);

    // Check if a valid action has been selected
    if (selectedAction() && !hasErrors())
    {
        // Execute action
        return executeAction(selectedAction());
    }

    // Print help
    print(help(selectedAction()));

    // Print errors
    if (hasErrors() && selectedAction())
    {
        // Print error message
        std::string error = selectedAction()->errors()[0];
        print("Error: " + error);

        // Indicate error condition
        return 1;
    }

    // Return without error
    return 0;
}

int CommandLineProgram::executeAction(CommandLineAction * action)
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

    // Reset status
    reset();

    // Find invoked action
    for (auto * action : m_actions)
    {
        // Parse command line
        action->parse(argc, argv);

        // Action found?
        if (action->activated())
        {
            m_selectedAction = action;
            return;
        }
    }
}

bool CommandLineProgram::hasErrors() const
{
    return (m_selectedAction && m_selectedAction->hasErrors());
}

CommandLineAction * CommandLineProgram::selectedAction() const
{
    return m_selectedAction;
}


} // namespace cppassist
