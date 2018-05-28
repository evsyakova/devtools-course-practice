// Copyright 2018 Aglikov Ilya

#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctime>

#include "include/queue.h"
#include "include/queue-app.h"

QueueApp::QueueApp() : message_("") {}

void QueueApp::help(const char* appname, const char* message) {
    message_ =
        std::string(message) +
          "This is a single-threaded processor simulation.\n\n" +
          "Please provide arguments in the following format:\n\n"+

          "  $ " + appname + " <clocks> <capacity>" +
          "<jobIntens> <procRate>\n\n" +

          "Where the " +
          "first argument <clocks> - number of simulation clock cycles, " +
          "second - <capacity> is queue size - positive integer number, " +
          "third - <jobIntens> is intensity of generation of a new task, " +
          "fourth - <procRate> is the processor performance.\n";
}

bool QueueApp::validateNumberOfArguments(int argc, const char** argv) {
    if (argc == 1) {
        help(argv[0]);
        return false;
    } else if (argc != 5) {
        help(argv[0], "ERROR: Should be 4 arguments.\n\n");
        return false;
    }
    return true;
}

double parseDouble(const char* arg) {
    char* end;
    double value = strtod(arg, &end);

    if (end[0]) {
        throw std::string("Wrong number format!");
    }

    return value;
}

int parseInt(const char* arg) {
    int value = std::stoi(std::string(arg));
    return value;
}

std::string QueueApp::operator()(int argc, const char** argv) {
    Arguments args;

    if (!validateNumberOfArguments(argc, argv)) {
        return message_;
    }
    try {
        args.clocks    = parseInt(argv[1]);
        args.capacity  = parseInt(argv[2]);
        args.jobIntens = parseDouble(argv[3]);
        args.procRate  = parseDouble(argv[4]);
    }
    catch(std::string& str) {
        return std::string("Wrong format or value is out of range");
    }

    Queue<int> queue(args.capacity);
    int clocks       = args.clocks;
    double jobIntens = args.jobIntens;
    double procRate  = args.procRate;

    int jobNumber   = 0;
    double denial   = 0;
    double downtime = 0;
    srand(time(0));

    for (int i = 0; i < clocks; i++) {
        if ((rand() % 100) < (jobIntens * 100)) {
            jobNumber++;
            if (!queue.full())
                queue.enqueue(jobNumber);
            else denial++;
        }
        if ((rand() % 100) < (procRate * 100))
            if (!queue.empty()) {
                queue.dequeue();
            } else {
                downtime++;
            }
    }

    denial = (int)(denial / jobNumber * 100);
    double avrCycles = ((double)clocks - downtime) / jobNumber;
    downtime = (int)(downtime / clocks * 100);

    std::ostringstream stream;
    stream << "Result of imitation:" 
        << "\nThe number of submitted jobs: " << jobNumber
        << "\nDenial of service (the queue is full): ~" <<  denial << '%'
        << "\nThe average number of quanta of the job: " << avrCycles
        << "\nDowntime of CPU (the queue is empty): ~" << downtime << '%';

    message_ = stream.str();

    return message_;
}
