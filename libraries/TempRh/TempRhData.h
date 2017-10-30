/*
 * TempRhData.h
 *
 * Author: Piotr Borkowski
 *
 */

#ifndef LIBRARIES_TEMPRH_TEMPRHDATA_H_
#define LIBRARIES_TEMPRH_TEMPRHDATA_H_

class TempRhData {
public:
	TempRhData();
	TempRhData(const float temp, const float rh);
	virtual ~TempRhData();

	float getTemp() const;
	float getRh() const;

private:
	float temperature;
	float relativeHumidity;
	static const int NO_TEMPERATURE = -256;
	static const int NO_HUMIDITY = -256;
};

#endif /* LIBRARIES_TEMPRH_TEMPRHDATA_H_ */
