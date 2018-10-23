#include "MAX77650.h"

MAX77650::MAX77650(PinName sda, PinName scl, int slaveAddress) : slaveAddress(slaveAddress) {
	i2c = new I2C(sda, scl);
	isOwner = true;
	resetToDefaults();
}

MAX77650::MAX77650(I2C *i2c, int slaveAddress) : slaveAddress(slaveAddress) {
	this->i2c = i2c;
	isOwner = false;
	resetToDefaults();
}

MAX77650::~MAX77650() {
	if(isOwner == true) {
		delete i2c;
	}
}

void MAX77650::resetToDefaults() {
	BOK = false;
	SBIA_LPM = false;
	SBIA_EN = false;
	nEN_MODE = false;
	DBEN_nEN = true;
	SFT_RST = SFT_RST_00;

	VCHGIN_MIN = VCHGIN_MIN_000;
	ICHGIN_LIM = ICHGIN_LIM_100;
	I_PQ = false;
	CHG_EN = true;

	TV_LDO = TV_LDO_1800;

	ADE_LDO = true;
	EN_LDO = EN_LDO_001;

	IP_SBB0 = IP_SBB0_00;
	TV_SBB0 = TV_SBB0_1800;
	ADE_SBB0 = true;
	EN_SBB0 = EN_SBB0_000;

	IP_SBB1 = IP_SBB1_00;
	TV_SBB1 = TV_SBB1_1200;
	ADE_SBB1 = true;
	EN_SBB1 = EN_SBB1_000;

	IP_SBB2 = IP_SBB2_00;
	TV_SBB2 = TV_SBB2_3300;
	ADE_SBB2 = true;
	EN_SBB2 = EN_SBB2_000;
}

int MAX77650::init() {
	char data;

	// CNFG_GLBL
	data = (BOK << 6) |
			(SBIA_LPM << 5) |
			(SBIA_EN << 4) |
			(nEN_MODE << 3) |
			(DBEN_nEN << 2) |
			(SFT_RST);

	if (writeReg(REG_CNFG_GLBL, data) != MAX77650_NO_ERROR) {
        return MAX77650_ERROR;
    }

    // CNFG_CHG_B
    data = (VCHGIN_MIN << 5) |
    		(ICHGIN_LIM << 2) |
    		(I_PQ << 1) |
    		(CHG_EN);

    if (writeReg(REG_CNFG_CHG_B, data) != MAX77650_NO_ERROR) {
        return MAX77650_ERROR;
    }

    // CNFG_LDO_A
    data = (TV_LDO);

    if (writeReg(REG_CNFG_LDO_A, data) != MAX77650_NO_ERROR) {
        return MAX77650_ERROR;
    }

    // CNFG_LDO_B
    data = (ADE_LDO << 3) |
    		(EN_LDO);

    if (writeReg(REG_CNFG_LDO_B, data) != MAX77650_NO_ERROR) {
        return MAX77650_ERROR;
    }

    // CNFG_SBB0_A
    data = (IP_SBB0 << 6) |
    		(TV_SBB0);

    if (writeReg(REG_CNFG_SBB0_A, data) != MAX77650_NO_ERROR) {
        return MAX77650_ERROR;
    }

    // CNFG_SBB0_B
    data = (ADE_SBB0 << 3) |
    		(EN_SBB0);

    if (writeReg(REG_CNFG_SBB0_B, data) != MAX77650_NO_ERROR) {
        return MAX77650_ERROR;
    }

    // CNFG_SBB1_A
    data = (IP_SBB1 << 6) |
    		(TV_SBB1);

    if (writeReg(REG_CNFG_SBB1_A, data) != MAX77650_NO_ERROR) {
        return MAX77650_ERROR;
    }

    // CNFG_SBB1_B
    data = (ADE_SBB1 << 3) |
    		(EN_SBB1);

    if (writeReg(REG_CNFG_SBB1_B, data) != MAX77650_NO_ERROR) {
        return MAX77650_ERROR;
    }

    // CNFG_SBB2_A
    data = (IP_SBB2 << 6) |
    		(TV_SBB2);

    if (writeReg(REG_CNFG_SBB2_A, data) != MAX77650_NO_ERROR) {
        return MAX77650_ERROR;
    }

    // CNFG_SBB2_B
    data = (ADE_SBB2 << 3) |
    		(EN_SBB2);

    if (writeReg(REG_CNFG_SBB2_B, data) != MAX77650_NO_ERROR) {
        return MAX77650_ERROR;
    }

    return MAX77650_NO_ERROR;
}

int MAX77650::writeReg(registers_t reg, char value) {
	char cmdData[2] = { (char)reg, value };

	if(i2c->write(slaveAddress, cmdData, sizeof(cmdData)) != 0) {
		return MAX77650_ERROR;
	}

	return MAX77650_NO_ERROR;
}

int MAX77650::readReg(registers_t reg, char *value) {
	char cmdData[1] = { (char)reg };

	if(i2c->write(slaveAddress, cmdData, sizeof(cmdData)) != 0) {
		return MAX77650_ERROR;
	}

	if(i2c->read(slaveAddress, value, 1) != 0) {
		return MAX77650_ERROR;
	}

	return MAX77650_NO_ERROR;
}
