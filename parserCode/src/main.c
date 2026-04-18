#include <stdio.h>
#include <commandParser.h>
#include <colorLogging.h>

int main(int argc, const char** argv)
{
    const unsigned int flagsFromCli = parseCommandsAndSetFlag(argc, argv);
    const unsigned int flagsFromToml = parseTomlIfExists();

    // Compare the flags from the process CLI and TOML decoding
    // Specifying the following behavior
    // 1) If the TOML file includes a flag but CLI not, then TOML has the prio
    // 2) If the TOML file doesn't include but CLI specifies, then CLI has the prio
    // 3) If the TOML file has in particular deactivated a flag and CLI specifies the same flag
    // as active, then CLI has the prio
    // 4) If the TOML file doesn't exist then you should generate a very basic file CMakeLists

    // THINK ABOUT THE INIT command -> which will actually create 
    return 0;
}

