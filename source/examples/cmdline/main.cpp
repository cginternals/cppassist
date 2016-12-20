
#include <cppassist/cppassist-version.h>

#include <cppassist/logging/logging.h>
#include <cppassist/cmdline/ArgumentParser.h>
#include <cppassist/cmdline/CommandLineProgram.h>
#include <cppassist/cmdline/CommandLineAction.h>
#include <cppassist/cmdline/CommandLineCommand.h>
#include <cppassist/cmdline/CommandLineOption.h>
#include <cppassist/cmdline/CommandLineSwitch.h>
#include <cppassist/cmdline/CommandLineParameter.h>


using namespace cppassist;


int main(int argc, char * argv[])
{
    // Declare program
    CommandLineProgram program(
        "cmdline-example",
        "cmdline-example " CPPASSIST_VERSION,
        "cmdline-example demonstrates how to parse (complex) command line options using the CommandLineProgram class in cppassist."
    );

        // Common options
        CommandLineSwitch swVerbose("--verbose", "-v", "Make output more verbose");

    // Action: 'help'
    CommandLineAction actionHelp("help", "Print help text");
    program.add(&actionHelp);

        actionHelp.add(&swVerbose);

        CommandLineSwitch swHelp("--help", "-h", "Print help text", CommandLineSwitch::NonOptional);
        actionHelp.add(&swHelp);

        CommandLineParameter paramCommand("command", CommandLineParameter::Optional);
        actionHelp.add(&paramCommand);

    // Action: 'count'
    CommandLineAction actionCount("count", "Count from one number to another");
    program.add(&actionCount);

        actionCount.add(&swVerbose);

        CommandLineCommand cmdCount("count");
        actionCount.add(&cmdCount);

        CommandLineOption optStep("--increment-by", "-i", "step", "Number that is added per iteration", CommandLineOption::Optional);
        actionCount.add(&optStep);

        CommandLineParameter paramFrom("from", CommandLineParameter::NonOptional);
        actionCount.add(&paramFrom);

        CommandLineParameter paramTo("to", CommandLineParameter::NonOptional);
        actionCount.add(&paramTo);

    // Action: 'cp'
    CommandLineAction actionCopy("cp", "Copy files");
    program.add(&actionCopy);

        actionCopy.add(&swVerbose);

        CommandLineCommand cmdCopy("cp");
        actionCopy.add(&cmdCopy);

        CommandLineParameter paramSrc("path", CommandLineParameter::NonOptional);
        actionCopy.add(&paramSrc);

        actionCopy.setOptionalParametersAllowed(true);
        actionCopy.setOptionalParameterName("path");

    // Parse command line
    program.parse(argc, argv);

    // Check if a valid action has been selected
    if (program.selectedAction() && !program.hasErrors())
    {
        // Display verbosity level
        info() << "Verbosity level: " << swVerbose.count() << std::endl;

        // Execute 'help'
        if (program.selectedAction() == &actionHelp)
        {
            CommandLineAction * forAction = nullptr;

            if (!paramCommand.value().empty())
            {
                forAction = program.getAction(paramCommand.value());
            }

            program.print(program.help(forAction));
        }

        // Execute 'count'
        else if (program.selectedAction() == &actionCount)
        {
            info() << "Let me count for you ..." << std::endl;
        }

        // Execute 'cp'
        else if (program.selectedAction() == &actionCopy)
        {
            info() << "Let me copy that for you ...";
            info() << "- " << actionCopy.getParameter("path")->value();

            for (auto arg : actionCopy.optionalParameters())
            {
                info() << "- " << arg;
            }
        }

        // Exit with success
        return 0;
    }

    // Print help
    program.print(program.help(program.selectedAction()));

    // Print errors
    if (program.hasErrors() && program.selectedAction())
    {
        // Print error message
        std::string error = program.selectedAction()->errors()[0];
        program.print("Error: " + error);

        return 1;
    }

    return 0;
}
