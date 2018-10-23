#ifndef _MAX77650_H_
#define _MAX77650_H_

#include "mbed.h"

#define MAX77650_NO_ERROR	0
#define MAX77650_ERROR		-1

class MAX77650 {
public:
	typedef enum {
		REG_CNFG_GLBL	 	= 0x10,
		REG_INT_GLBL 		= 0x00,
		REG_INTM_GLBL 		= 0x06,
		REG_STAT_GLBL 		= 0x05,
		REG_ERCFLAG 		= 0x04,
		REG_CNFG_GPIO 		= 0x12,
		REG_CID 			= 0x11,
		REG_INT_CHG			= 0x01,
		REG_INT_M_CHG		= 0x07,
		REG_STAT_CHG_A		= 0x02,
		REG_STAT_CHG_B		= 0x03,
		REG_CNFG_CHG_A		= 0x18,
		REG_CNFG_CHG_B		= 0x19,
		REG_CNFG_CHG_C		= 0x1A,
		REG_CNFG_CHG_D		= 0x1B,
		REG_CNFG_CHG_E		= 0x1C,
		REG_CNFG_CHG_F 		= 0x1D,
		REG_CNFG_CHG_G		= 0x1E,
		REG_CNFG_CHG_H		= 0x1F,
		REG_CNFG_CHG_I		= 0x20,
		REG_CNFG_LDO_A		= 0x38,
		REG_CNFG_LDO_B		= 0x39,
		REG_CNFG_SBB_TOP	= 0x28,
		REG_CNFG_SBB0_A		= 0x29,
		REG_CNFG_SBB0_B		= 0x2A,
		REG_CNFG_SBB1_A		= 0x2B,
		REG_CNFG_SBB1_B		= 0x2C,
		REG_CNFG_SBB2_A		= 0x2D,
		REG_CNFG_SBB2_B		= 0x2E,
		REG_CNFG_LED0_A		= 0x40,
		REG_CNFG_LED0_B		= 0x43,
		REG_CNFG_LED1_A		= 0x41,
		REG_CNFG_LED1_B		= 0x44,
		REG_CNFG_LED2_A		= 0x42,
		REG_CNFG_LED2_B		= 0x43,
		REG_CNFG_LED_TOP	= 0x46
	} registers_t;

	/*
	 * @brief	Software Reset Functions
	 */
	typedef enum {
		SFT_RST_00,			// No Action
		SFT_RST_01,			// Software Cold Reset
		SFT_RST_10,			// Software Off
		SFT_RST_11			// Reserved
	} SFT_RST_t;

	/*
	 * @brief	Device Identification Bits for Metal Options 
	 */
	typedef enum {
		DIDM_00,			// MAX77650
		DIDM_01,			// MAX77651
		DIDM_10,			// Reserved
		DIDM_11				// Reserved
	} DIDM_t;
	
	/*
	 * @brief	Sampling Clock Frequency
	 */
	typedef enum {
		CLKS_011	= 0x3,	// 160Hz
		CLKS_100	= 0x4,	// 80Hz
		CLKS_101 	= 0x5,	// 40Hz
		CLKS_110 	= 0x6,	// 20Hz
		CLKS_111 	= 0x7 	// 10Hz
	} CLKS_t;

	/*
	 * @brief	Chip Identification Code
	 */
	typedef enum {
		MAX77650A	= 0x3,
		MAX77650C	= 0xA,
		MAX77651A	= 0x6,
		MAX77651B	= 0x8
	} CID_t;

	/*
	 * @brief	Battery Temperature Details
	 */
	typedef enum {
		THM_DTLS_000,		// Thermistor is disabled (THM_EN = 0)
		THM_DTLS_001,		// Battery is cold as programmed by THM_COLD
		THM_DTLS_010,		// Battery is cool as programmed by THM_COOL
		THM_DTLS_011,		// Battery is warm as programmed by THM_WARM
		THM_DTLS_100,		// Battery is hot as programmed by THM_HOT
		THM_DTLS_101,		// Battery is in the normal temperature region as programmed by THM_CONTROL
		THM_DTLS_110,		// Reserved
		THM_DTLS_111		// Reserved
	} THM_DTLS_t;

	/*
	 * @brief	Charger Details
	 */
	typedef enum {
		CHG_DTLS_0000,
		CHG_DTLS_0001,
		CHG_DTLS_0010,
		CHG_DTLS_0011,
		CHG_DTLS_0100,
		CHG_DTLS_0101,
		CHG_DTLS_0110,
		CHG_DTLS_0111,
		CHG_DTLS_1000,
		CHG_DTLS_1001,
		CHG_DTLS_1010,
		CHG_DTLS_1011,
		CHG_DTLS_1100,
		CHG_DTLS_1101,
		CHG_DTLS_1110,
		CHG_DTLS_1111
	} CHG_DTLS_t;

	/*
	 * @brief	CHGIN Status Details
	 */
	typedef enum {
		CHGIN_DTLS_00,
		CHGIN_DTLS_01,
		CHGIN_DTLS_10,
		CHGIN_DTLS_11
	} CHGIN_DTLS_t;

	/*
	 * @brief	VHOT JEITA Temperature Threshold
	 */
	typedef enum {
		THM_HOT_00,
		THM_HOT_01,
		THM_HOT_10,
		THM_HOT_11
	} THM_HOT_t;

	/*
	 * @brief	VWARM JEITA Temperature Threshold
	 */
	typedef enum {
		THM_WARM_00,
		THM_WARM_01,
		THM_WARM_10,
		THM_WARM_11
	} THM_WARM_t;
	
	/*
	 * @brief	VCOOL JEITA Temperature Threshold
	 */
	typedef enum {
		THM_COOL_00,
		THM_COOL_01,
		THM_COOL_10,
		THM_COOL_11
	} THM_COOL_t;
	
	/*
	 * @brief	VCOLD JEITA Temperature Threshold
	 */
	typedef enum {
		THM_COLD_00,
		THM_COLD_01,
		THM_COLD_10,
		THM_COLD_11
	} THM_COLD_t;

	/*
	 * @brief	Minimum CHGIN regulation voltage
	 */
	typedef enum {
		VCHGIN_MIN_000,
		VCHGIN_MIN_001,
		VCHGIN_MIN_010,
		VCHGIN_MIN_011,
		VCHGIN_MIN_100,
		VCHGIN_MIN_101,
		VCHGIN_MIN_110,
		VCHGIN_MIN_111
	} VCHGIN_MIN_t;
	
	/*
	 * @brief	CHGIN Input Current Limit
	 */
	typedef enum {
		ICHGIN_LIM_000,
		ICHGIN_LIM_001,
		ICHGIN_LIM_010,
		ICHGIN_LIM_011,
		ICHGIN_LIM_100,
		ICHGIN_LIM_101,
		ICHGIN_LIM_110,
		ICHGIN_LIM_111
	} ICHGIN_LIM_t;
	
	/*
	 * @brief	Battery prequalification voltage threshold
	 */
	typedef enum {
		CHG_PQ_000,
		CHG_PQ_001,
		CHG_PQ_010,
		CHG_PQ_011,
		CHG_PQ_100,
		CHG_PQ_101,
		CHG_PQ_110,
		CHG_PQ_111
	} CHG_PQ_t;
	
	/*
	 * @brief	Charger Termination Current
	 */
	typedef enum {
		I_TERM_00,
		I_TERM_01,
		I_TERM_10,
		I_TERM_11
	} I_TERM_t;
	
	/*
	 * @brief	Topoff Timer Value
	 */
	typedef enum {
		T_TOPOFF_000,
		T_TOPOFF_001,
		T_TOPOFF_010,
		T_TOPOFF_011,
		T_TOPOFF_100,
		T_TOPOFF_101,
		T_TOPOFF_110,
		T_TOPOFF_111
	} T_TOPOFF_t;

	/*
	 * @brief	Die Junction Temperature Regulation Point
	 */
	typedef enum {
		TJ_REG_000,
		TJ_REG_001,
		TJ_REG_010,
		TJ_REG_011,
		TJ_REG_100,
		TJ_REG_101,
		TJ_REG_110,
		TJ_REG_111
	} TJ_REG_t;
	
	/*
	 * @brief	System Voltage Regulation
	 */
	typedef enum {
		VSYS_4800 = 0x1F
	} VSYS_REG_t;

	/*
	 * @brief	Fast-Charge Constant Current Value
	 */
	typedef enum {
		CHG_CC_300 = 0x3F
	} CHG_CC_t;
	
	/*
	 * @brief	Fast-Charge Safety Timer
	 */
	typedef enum {
		T_FAST_CHG_00,
		T_FAST_CHG_01,
		T_FAST_CHG_10,
		T_FAST_CHG_11
	} T_FAST_CHG_t;

	/*
	 * @brief	I_{FAST-CHG_JEITA}
	 */
	typedef enum {
		CHG_CC_JEITA_300 = 0x3F
	} CHG_CC_JEITA_t;

	/*
	 * @brief	Fast-Charge Battery Regulation Voltage
	 */
	typedef enum {
		CHG_CV_4600 = 0x3F
	} CHG_CV_t;

	/*
	 * @brief	Modified V_{FAST-CHG}
	 */
	typedef enum {
		CHG_CV_JEITA_4600 = 0x3F
	} CHG_CV_JEITA_t;

	/*
	 * @brief	Battery Discharge Current Full-Scale Current Value
	 */
	typedef enum {
		IMON_DISCHG_SCALE_300 = 0x0F
	} IMON_DISCHG_SCALE_t;

	/*
	 * @brief	Analog Channel to Connect to AMUX
	 */
	typedef enum {
		MUX_SEL_BATT_V = 0x3
	} MUX_SEL_t;

	/*
	 * @brief	LDO Target Output Voltage
	 */
	typedef enum {
		TV_LDO_1800 = 0x24
	} TV_LDO_t;

	/*
	 * @brief	Enable Control for LDO
	 */
	typedef enum {
		EN_LDO_000,
		EN_LDO_001,
		EN_LDO_010,
		EN_LDO_011,
		EN_LDO_100,
		EN_LDO_101,
		EN_LDO_110,
		EN_LDO_111
	} EN_LDO_t;

	/*
	 * @brief	SIMO Buck-Boost Drive Strength Trim
	 */
	typedef enum {
		DRV_SBB_00,
		DRV_SBB_01,
		DRV_SBB_10,
		DRV_SBB_11
	} DRV_SBB_t;

	/*
	 * @brief	SIMO Buck-Boost Channel 0 Peak Current Limit
	 */
	typedef enum {
		IP_SBB0_00,
		IP_SBB0_01,
		IP_SBB0_10,
		IP_SBB0_11
	} IP_SBB0_t;

	/*
	 * @brief	SIMO Buck-Boost Channel 0 Target Output Voltage
	 */
	typedef enum {
		TV_SBB0_1800 = 0x28
	} TV_SBB0_t;

	/*
	 * @brief	Enable Control For SIMO Buck-Boost Channel 0
	 */
	typedef enum {
		EN_SBB0_000,
		EN_SBB0_001,
		EN_SBB0_010,
		EN_SBB0_011,
		EN_SBB0_100,
		EN_SBB0_101,
		EN_SBB0_110,
		EN_SBB0_111
	} EN_SBB0_t;

	/*
	 * @brief	SIMO Buck-Boost Channel 1 Peak Current Limit
	 */
	typedef enum {
		IP_SBB1_00,
		IP_SBB1_01,
		IP_SBB1_10,
		IP_SBB1_11
	} IP_SBB1_t;

	/*
	 * @brief	SIMO Buck-Boost Channel 1 Target Output Voltage
	 */
	typedef enum {
		TV_SBB1_1200 = 0x20
	} TV_SBB1_t;

	/*
	 * @brief	Enable Control For SIMO Buck-Boost Channel 1
	 */
	typedef enum {
		EN_SBB1_000,
		EN_SBB1_001,
		EN_SBB1_010,
		EN_SBB1_011,
		EN_SBB1_100,
		EN_SBB1_101,
		EN_SBB1_110,
		EN_SBB1_111
	} EN_SBB1_t;

	/*
	 * @brief	SIMO Buck-Boost Channel 2 Peak Current Limit
	 */
	typedef enum {
		IP_SBB2_00,
		IP_SBB2_01,
		IP_SBB2_10,
		IP_SBB2_11
	} IP_SBB2_t;

	/*
	 * @brief	SIMO Buck-Boost Channel 2 Target Output Voltage
	 */
	typedef enum {
		TV_SBB2_3300 = 0x32
	} TV_SBB2_t;

	/*
	 * @brief	Enable Control For SIMO Buck-Boost Channel 2
	 */
	typedef enum {
		EN_SBB2_000,
		EN_SBB2_001,
		EN_SBB2_010,
		EN_SBB2_011,
		EN_SBB2_100,
		EN_SBB2_101,
		EN_SBB2_110,
		EN_SBB2_111
	} EN_SBB2_t;

	/*
	 * @brief	LED0 Full Scale Range
	 */
	typedef enum {
		LED_FS0_00,
		LED_FS0_01,
		LED_FS0_10,
		LED_FS0_11
	} LED_FS0_t;

	/*
	 * @brief	LED0 Brightness Control
	 */
	typedef enum {
		BRT_LED0_1F = 0x1F
	} BRT_LED0_t;

	/*
	 * @brief	LED0 Period Settings
	 */
	typedef enum {
		P_LED0_3 = 0x5 		// 3.0s
	} P_LED0_t;

	/*
	 * @brief	LED0 On Duty-Cycle Settings
	 */
	typedef enum {
		D_LED0_50 = 0x7 	// 50%
	} D_LED0_t;

	/*
	 * @brief	LED1 Full Scale Range
	 */
	typedef enum {
		LED_FS1_00,
		LED_FS1_01,
		LED_FS1_10,
		LED_FS1_11
	} LED_FS1_t;

	/*
	 * @brief	LED1 Brightness Control
	 */
	typedef enum {
		BRT_LED1_1F = 0x1F
	} BRT_LED1_t;

	/*
	 * @brief	LED1 Period Settings
	 */
	typedef enum {
		P_LED1_3 = 0x5 		// 3.0s
	} P_LED1_t;

	/*
	 * @brief	LED1 On Duty-Cycle Settings
	 */
	typedef enum {
		D_LED1_50 = 0x7 	// 50%
	} D_LED1_t;

	/*
	 * @brief	LED2 Full Scale Range
	 */
	typedef enum {
		LED_FS2_00,
		LED_FS2_01,
		LED_FS2_10,
		LED_FS2_11
	} LED_FS2_t;

	/*
	 * @brief	LED2 Brightness Control
	 */
	typedef enum {
		BRT_LED2_1F = 0x1F
	} BRT_LED2_t;

	/*
	 * @brief	LED2 Period Settings
	 */
	typedef enum {
		P_LED2_3 = 0x5 		// 3.0s
	} P_LED2_t;

	/*
	 * @brief	LED2 On Duty-Cycle Settings
	 */
	typedef enum {
		D_LED2_50 = 0x7 	// 50%
	} D_LED2_t;


	MAX77650(PinName sda, PinName scl, int slaveAddress);

	MAX77650(I2C *i2c, int slaveAddress);

	~MAX77650();

	int init();

	void resetToDefaults();

	int writeReg(registers_t reg, char value);

	int readReg(registers_t reg, char *value);

	bool BOK;
	bool SBIA_LPM;
	bool SBIA_EN;
	bool nEN_MODE;
	bool DBEN_nEN;
	SFT_RST_t SFT_RST;

	bool DOD_R;
	bool TJAL2_R;
	bool TJAL1_R;
	bool nEN_R;
	bool nEN_F;
	bool GPI_R;
	bool GPI_F;

	bool DOD_RM;
	bool TJAL2_RM;
	bool TJAL1_RM;
	bool nEN_RM;
	bool nEN_FM;
	bool GPI_RM;
	bool GPI_FM;

	DIDM_t DIDM;
	bool DOD_S;
	bool TJAL2_S;
	bool TJAL1_S;
	bool STAT_EN;
	bool STAT_PWR_HLD;
	bool STAT_IRQ;

	bool PWR_HLD_RST;
	bool SFT_CRST_F;
	bool SFT_OFF_F;
	bool MRST;
	bool SYSUVLO;
	bool SYSOVLO;
	bool TOVLD;

	bool DBEN_GPI;
	bool DO;
	bool DRV;
	bool DI;
	bool DIR;

	CLKS_t CLKS;
	CID_t CID;

	bool SYS_CNFG_I;
	bool SYS_CTRL_I;
	bool CHGIN_CTRL_I;
	bool TJ_REG_I;
	bool CHGIN_I;
	bool CHG_I;
	bool THM_I;

	bool SYS_CNFG_M;
	bool SYS_CTRL_M;
	bool CHGIN_CTRL_M;
	bool TJ_REG_M;
	bool CHGIN_M;
	bool CHG_M;
	bool THM_M;

	bool VCHGIN_MIN_STAT;
	bool ICHGIN_LIM_STAT;
	bool VSYS_MIN_STAT;
	bool TJ_REG_STAT;
	THM_DTLS_t THM_DTLS;

	CHG_DTLS_t CHG_DTLS;
	CHGIN_DTLS_t CHGIN_DTLS;
	bool CHG;
	bool TIME_SUS;

	THM_HOT_t THM_HOT;
	THM_WARM_t THM_WARM;
	THM_COOL_t THM_COOL;
	THM_COLD_t THM_COLD;

	VCHGIN_MIN_t VCHGIN_MIN;
	ICHGIN_LIM_t ICHGIN_LIM;
	bool I_PQ;
	bool CHG_EN;

	CHG_PQ_t CHG_PQ;
	I_TERM_t I_TERM;
	T_TOPOFF_t T_TOPOFF;

	TJ_REG_t TJ_REG;
	VSYS_REG_t VSYS_REG;

	CHG_CC_t CHG_CC;
	T_FAST_CHG_t T_FAST_CHG;

	CHG_CC_JEITA_t CHG_CC_JEITA;
	bool THM_EN;

	CHG_CV_t CHG_CV;
	bool USBS;

	CHG_CV_JEITA_t CHG_CV_JEITA;

	IMON_DISCHG_SCALE_t IMON_DISCHG_SCALE;
	MUX_SEL_t MUX_SEL;

	TV_LDO_t TV_LDO;

	bool ADE_LDO;
	EN_LDO_t EN_LDO;

	bool MRT_OTP;
	bool SBIA_LPM_DEF;
	bool DBNC_nEN_DEF;
	DRV_SBB_t DRV_SBB;

	IP_SBB0_t IP_SBB0;
	TV_SBB0_t TV_SBB0;

	bool ADE_SBB0;
	EN_SBB0_t EN_SBB0;

	IP_SBB1_t IP_SBB1;
	TV_SBB1_t TV_SBB1;

	bool ADE_SBB1;
	EN_SBB1_t EN_SBB1;

	IP_SBB2_t IP_SBB2;
	TV_SBB2_t TV_SBB2;

	bool ADE_SBB2;
	EN_SBB2_t EN_SBB2;

	LED_FS0_t LED_FS0;
	bool INV_LED0;
	BRT_LED0_t BRT_LED0;

	P_LED0_t P_LED0;
	D_LED0_t D_LED0;

	LED_FS1_t LED_FS1;
	bool INV_LED1;
	BRT_LED1_t BRT_LED1;

	P_LED1_t P_LED1;
	D_LED1_t D_LED1;

	LED_FS2_t LED_FS2;
	bool INV_LED2;
	BRT_LED2_t BRT_LED2;

	P_LED2_t P_LED2;
	D_LED2_t D_LED2;

	bool CLK_64_S;
	bool EN_LED_MSTR;

private:
	I2C *i2c;
	bool isOwner;
	int slaveAddress;
};

#endif /* _MAX77650_H_ */
