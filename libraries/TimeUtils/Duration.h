/*
 * Duration.h
 *
 * Author: Piotr Borkowski
 *
 * Utility class useful for defining duration.
 */

#ifndef TIMEUTILS_DURATION_H_
#define TIMEUTILS_DURATION_H_

#include <stdint.h>

typedef uint32_t DurationUnit;

class Duration {
public:
    Duration();
    virtual ~Duration();

    enum TimeBase {
        MILIS = 1000, MICROS = 1000 * MILIS,
    };

    /**
     * Creates duration for given seconds.
     * @param seconds Seconds number
     * @param base Base to be used for creating duration.
     *        May be {@link MILIS} or {@link MICROS}
     */
    static DurationUnit Seconds(uint8_t seconds, TimeBase base = MILIS);

    /**
     * Creates duration for given minutes.
     * @param seconds Minutes number
     * @param base Base to be used for creating duration.
     *        May be {@link MILIS} or {@link MICROS}
     */
    static DurationUnit Minutes(uint8_t minutes, TimeBase base = MILIS);

private:
    static const uint8_t SECONDS_IN_MINUTE = 60;
};

#endif /* TIMEUTILS_DURATION_H_ */
