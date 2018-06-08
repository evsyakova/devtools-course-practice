// Copyright 2018 Evsyakova Ekaterina

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include <vector>
#include <string>
#include <sstream>

#include "include/arbitrary_precision_calculator.h"
#include "include/arbitrary_precision_calculator_app.h"

ArbitraryPrecisionCalculatorApp::
ArbitraryPrecisionCalculatorApp() : message_("") {}

void ArbitraryPrecisionCalculatorApp::help(const char* appname,
    const char* message) {
    message_ =
        std::string(message) +
        "This is an arbitrary precision calculator application.\n\n" +
        "Please provide arguments in the following format:\n\n" +

        "  $ " + appname + " <left_operand> <right_operand> <operation>\n\n" +

        "Where all arguments are integer (infinite-precision) numbers, " +
        "and <operation> is one of '+', '-', '*', '/'.\n";
}

bool ArbitraryPrecisionCalculatorApp::validateNumberOfArguments
(int argc, const char** argv) {
    if (argc == 1) {
        help(argv[0]);
        return false;
    } else if (argc != 4) {
        help(argv[0], "ERROR: Should be 3 arguments.\n\n");
        return false;
    }
    return true;
}

std::vector <int> parseNumber(const char* arg) {
    int i = 0;
    while (arg[i] != '\0') {
        if (!(arg[i] == '\0' || arg[i] == '-' ||
            (arg[i] >= 48 && arg[i] <= 57))) {
            throw std::string("Wrong number format!");
        }
        i++;
    }

    std::vector <int> number;
    i--;
    while (i > 1) {
        number.push_back(static_cast<int>(arg[i]) - 48);
        i--;
    }

    if (arg[0] == '-') {
        number.push_back(-1 * (static_cast<int>(arg[1]) - 48));
    } else {
        if (arg[1] != '\0')
            number.push_back(static_cast<int>(arg[1]) - 48);
        number.push_back(static_cast<int>(arg[0]) - 48);
    }

    ArbitraryPrecisionCalculator z;
    number = z.reverseVector(number);

    return number;
}

char parseOperation(const char* arg) {
    char operation;
    if (strcmp(arg, "+") == 0) {
        operation = '+';
    } else if (strcmp(arg, "-") == 0) {
        operation = '-';
    } else if (strcmp(arg, "*") == 0) {
        operation = '*';
    } else if (strcmp(arg, "/") == 0) {
        operation = '/';
    } else {
        throw std::string("Wrong operation format!");
    }
    return operation;
}

std::string ArbitraryPrecisionCalculatorApp::operator()
(int argc, const char** argv) {
    Arguments args;

    if (!validateNumberOfArguments(argc, argv)) {
        return message_;
    }
    try {
        args.left_operand = parseNumber(argv[1]);
        args.right_operand = parseNumber(argv[2]);
        args.operation = parseOperation(argv[3]);
    }
    catch (std::string& str) {
        return str;
    }

    ArbitraryPrecisionCalculator z1;
    ArbitraryPrecisionCalculator z2;

    z1.setNumber(args.left_operand);
    z2.setNumber(args.right_operand);

    ArbitraryPrecisionCalculator z;
    std::ostringstream stream;

    switch (args.operation) {
    case '+':
        z = z1 + z2;
        stream << "Result: " << z.getResultInString();
        break;
    case '-':
        z = z1 - z2;
        stream << "Result: " << z.getResultInString();
        break;
    case '*':
        z = z1 * z2;
        stream << "Result: " << z.getResultInString();
        break;
    case '/':
        try {
            z = z1 / z2;
            stream << "Result: " << z.getResultInString();
            break;
        }
        catch (std::string& str) {
            return str;
        }
    }

    message_ = stream.str();

    return message_;
}
