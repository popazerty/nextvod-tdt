#ifndef __lib_driver_rcconsole_h
#define __lib_driver_rcconsole_h

#include <termios.h>
#include <lib/driver/rc.h>

class eRCConsoleDriver: public eRCDriver
{
	struct termios ot;
	void init_eRCConsoleDriver(const char *filename);
protected:
	int handle;
	eSocketNotifier *sn;
	void keyPressed(int);
public:
	eRCConsoleDriver(const char *filename);
	~eRCConsoleDriver();
	void flushBuffer() const
	{
		char data[16];
		if (handle != -1)
			while ( ::read(handle, data, 16) == 16 );
	}
	void lock() const
	{
		if ( sn )
			sn->stop();
	}
	void unlock() const
	{
		if ( sn )
			sn->start();
	}
};

class eRCConsole: public eRCDevice
{
public:
	void handleCode(int code);
	eRCConsole(eRCDriver *driver);
	const char *getDescription() const;
	const char *getKeyDescription(const eRCKey &key) const;
	int getKeyCompatibleCode(const eRCKey &key) const;
};

#endif
