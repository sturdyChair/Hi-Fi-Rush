#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
#include "Effect_Base.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CModel;
END


BEGIN(Client)

class CBeamCylinder : public CEffect_Base
{
public:
	static wstring ObjID;

private:
	CBeamCylinder(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CBeamCylinder(const CBeamCylinder& rhs);

public:
	virtual ~CBeamCylinder();

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void PriorityTick(_float fTimeDelta);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

public:
	virtual void EffectStartCallBack();
	virtual void EffectEndCallBack();

	virtual void EffectSoftEnd();
	virtual void EffectHardEnd();

private:
	shared_ptr<CShader> m_pShaderCom = { nullptr };
	shared_ptr<CModel> m_pModelCom = { nullptr };
	shared_ptr<CTexture> m_pTextureCom = { nullptr };
	shared_ptr<CTexture> m_pNoiseTextureCom = { nullptr };

	_float m_fTimer = 0.f;

private:
	HRESULT Ready_Components();

public:
	static shared_ptr<CBeamCylinder> Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual shared_ptr<CGameObject> Clone(void* pArg) override;
	void Free();
};

END