#define SCANMODE_OPTION_COUNT 3
const CMenuOptionChooser::keyval SCANMODE_OPTIONS[SCANMODE_OPTION_COUNT] =
{
	{ 0, LOCALE_EXTRA_SCAN_FULL},
	{ 1, LOCALE_EXTRA_SCAN_FAST},
	{ 2, LOCALE_EXTRA_TPSCAN}
};

#define HDD_NOISE_OPTION_COUNT 4
const CMenuOptionChooser::keyval HDD_NOISE_OPTIONS[HDD_NOISE_OPTION_COUNT] =
{
	{0, LOCALE_OPTIONS_OFF},
	{128, LOCALE_HDD_SLOW},
	{190, LOCALE_HDD_MIDDLE},
	{254, LOCALE_HDD_FAST}
};
#define HDD_FILESYS_OPTION_COUNT 2
const CMenuOptionChooser::keyval HDD_FILESYS_OPTIONS[HDD_FILESYS_OPTION_COUNT] =
{
	{0, LOCALE_HDD_EXT3},
	{1, LOCALE_HDD_EXT2} /*,
	{2, LOCALE_HDD_REISER} */
};
#define HDD_SLEEP_OPTION_COUNT 7
const CMenuOptionChooser::keyval HDD_SLEEP_OPTIONS[HDD_SLEEP_OPTION_COUNT] =
{
	{0, LOCALE_OPTIONS_OFF},
	{12, LOCALE_HDD_1MIN},
	{60, LOCALE_HDD_5MIN},
	{120, LOCALE_HDD_10MIN},
	{240, LOCALE_HDD_20MIN},
	{241, LOCALE_HDD_30MIN},
	{242, LOCALE_HDD_60MIN}
};
#if 0
#define LOGO_OPTION_COUNT 3
const CMenuOptionChooser::keyval LOGO_OPTIONS[LOGO_OPTION_COUNT] =
{
	{1, LOCALE_EXTRA_LOGO1},
	{2, LOCALE_EXTRA_LOGO2},
	{3, LOCALE_EXTRA_LOGO3}
};
#endif
#define RF_CARRIER_OPTION_COUNT 4
const CMenuOptionChooser::keyval RF_CARRIER_OPTIONS[RF_CARRIER_OPTION_COUNT] =
{
	{0, LOCALE_RF_CARRIER_4500},
	{1, LOCALE_RF_CARRIER_5500},
	{2, LOCALE_RF_CARRIER_6000},
	{3, LOCALE_RF_CARRIER_6500}
};
#define OPTIONS_SOUTH0_NORTH1_OPTION_COUNT 2
const CMenuOptionChooser::keyval OPTIONS_SOUTH0_NORTH1_OPTIONS[OPTIONS_SOUTH0_NORTH1_OPTION_COUNT] =
{
	{0, LOCALE_EXTRA_SOUTH},
	{1, LOCALE_EXTRA_NORTH}
};
#define OPTIONS_EAST0_WEST1_OPTION_COUNT 2
const CMenuOptionChooser::keyval OPTIONS_EAST0_WEST1_OPTIONS[OPTIONS_EAST0_WEST1_OPTION_COUNT] =
{
	{0, LOCALE_EXTRA_EAST},
	{1, LOCALE_EXTRA_WEST}
};
