#include <stdio.h>
#include "../header/coloring.h"
#include "../header/ascii.h"

void printBanner() {
    printf(BRIGHT_YELLOW
    "  ____  _   _ __  __    _    _   _   ____    _    _  _____ _____ \n");
    printf(BRIGHT_YELLOW
    " |  _ \\| | | |  \\/  |  / \\  | | | | / ___|  / \\  | |/ /_ _|_   _|\n");
    printf(BRIGHT_CYAN
    " | |_) | | | | |\\/| | / _ \\ | |_| | \\___ \\ / _ \\ | ' / | |  | |  \n");
    printf(BRIGHT_CYAN
    " |  _ <| |_| | |  | |/ ___ \\|  _  |  ___) / ___ \\| . \\ | |  | |  \n");
    printf(BRIGHT_BLUE
    " |_| \\_\\\\___/|_|__|_/_/  _\\_\\_|_|_| |____/_/   \\_\\_|\\_\\___| |_|  \n");
    printf(BRIGHT_MAGENTA
    " | \\ | |_ _|  \\/  |/ _ \\| \\ | / ___|                             \n");
    printf(BRIGHT_MAGENTA
    " |  \\| || || |\\/| | | | |  \\| \\___ \\                             \n");
    printf(BRIGHT_MAGENTA
    " | |\\  || || |  | | |_| | |\\  |___) |                            \n");
    printf(BRIGHT_MAGENTA
    " |_| \\_|___|_|  |_|\\___/|_| \\_|____/                             \n");
    printf(RESET);
}



void printSembuh() {
    printf(YELLOW
    "                                                ,---. \n"
    RESET CYAN
    " ,---.                  ,--.           ,--.     |   | \n"
    RESET GREEN
    "'   .-' ,---. ,--,--,--.|  |-. ,--.,--.|  ,---. |  .' \n"
    RESET BLUE
    "`.  `-.| .-. :|        || .-. '|  ||  ||  .-.  ||  |  \n"
    RESET MAGENTA
    ".-'    \\   --.|  |  |  || `-' |'  ''  '|  | |  |`--'  \n"
    RESET RED
    "`-----' `----'`--`--`--' `---'  `----' `--' `--'.--.  \n"
    RESET YELLOW
    "                                                '--'  \n"
    RESET
    );
}

void printDead() {
    printf(RED
    "                                               \n"
    ",------.                    ,--.          ,-. \n"
    "|  .-.  \\  ,---.  ,--,--. ,-|  |    .--. / .' \n"
    "|  |  \\  :| .-. :' ,-.  |' .-. |    '--'|  |  \n"
    "|  '--'  /\\   --.\\ '-'  |\\ `-' |    .--.|  |  \n"
    "`-------'  `----' `--`--' `---'     '--' \\ '. \n"
    "                                          `-'  \n"
    RESET);
}



