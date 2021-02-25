#include "Includes.h"

DWORD Entidad::getEntityBase(int index)
{
	return readMem<DWORD>(gameModule + signatures::dwEntityList + (index * 0x10));
}

int	Entidad::getEntHp(DWORD playerBase)
{
	return readMem<int>(playerBase + netvars::m_iHealth);
}

bool Entidad::isAlive(DWORD playerBase)
{
	if (getEntHp(playerBase) > 0 && getEntHp(playerBase) <= 100)
		return true;
	return false;
}

int	Entidad::getEntTeam(DWORD playerBase)
{
	return readMem<int>(playerBase + netvars::m_iTeamNum);
}

int Entidad::getGlowIndex(DWORD playerBase)
{
	return readMem<int>(playerBase + netvars::m_iGlowIndex);
}

DWORD Entidad::getGlowObj()
{
	return readMem<DWORD>(gameModule + signatures::dwGlowObjectManager);
}

bool Entidad::isValid(DWORD playerBase)
{
	auto dormant = readMem<bool>(playerBase + signatures::m_bDormant);
	if ((Entidad::isAlive(playerBase) && Entidad::getEntTeam(playerBase) != 0) && !dormant)
		return true;
	return false;
}

void Entidad::glowEsp(DWORD glowObj, int glowInd, float r, float g, float b, float a)
{
	writeMem<float>((glowObj + ((glowInd * 0x38) + 0x4)), r / 255);
	writeMem<float>((glowObj + ((glowInd * 0x38) + 0x8)), g / 255);
	writeMem<float>((glowObj + ((glowInd * 0x38) + 0xC)), b / 255);
	writeMem<float>((glowObj + ((glowInd * 0x38) + 0x10)), a / 255);
	writeMem<bool>((glowObj + ((glowInd * 0x38) + 0x24)), true);
	writeMem<bool>((glowObj + ((glowInd * 0x38) + 0x25)), false);
	//writeMem< bool >((glowObj + ((glowInd * 0x38) + 0x26)), true);
}

bool Entidad::getSpotted(DWORD base)
{
	return readMem<bool>(base + netvars::m_bSpotted);
}

void Entidad::setSpotted(DWORD base, bool val)
{
	writeMem<bool>(base + netvars::m_bSpotted, val);
}

bool Entidad::getEntImmunity(DWORD base)
{
	return readMem<bool>(base + netvars::m_bGunGameImmunity);
}

DWORD Entidad::getEntBoneMatrix(DWORD base)
{
	return readMem<DWORD>(base + netvars::m_dwBoneMatrix);
}

D3DXVECTOR3	Entidad::getEntBonePos(DWORD base, int boneID)
{
	Matrix3x4_t boneMatrix = readMem<Matrix3x4_t>(Entidad::getEntBoneMatrix(base) + boneID * 0x30);

	return{
		boneMatrix.Matrix[0][3],
		boneMatrix.Matrix[1][3],
		boneMatrix.Matrix[2][3]
	};
}

D3DXVECTOR3	Entidad::getEntPos(DWORD base)
{
	return readMem<D3DXVECTOR3>(base + netvars::m_vecOrigin);
}