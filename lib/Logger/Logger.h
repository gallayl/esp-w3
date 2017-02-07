#ifndef LOGGER_H_
#define LOGGER_H_

#include <Arduino.h>

class Logger {
public:
	Logger();
	virtual ~Logger();

    static void Write(String entry);
    static void Write(int entry);

    static void WriteLine(String entry);
    static void WriteLine(int entry);

    static size_t print(const Printable&);
};

#endif /* LOGGER_H_ */
