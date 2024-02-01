#include "../[000]Object/[000]Stage/[000]SkyBox/SkyBox.h"
#include "../[000]Object/[001]Character/[003]Butterfly/Butterfly.h"
#include "../[000]Object/[001]Character/[003]Butterfly/[000]ButterflyFunction/ButterflyLoad.h"
#include "../[001]Camera/OpCamera.h"
#include "../[002]Mediator/Mediator.h"
#include "OpFactory.h"


OpFactory::OpFactory()
{
	CreateObject();

	SetObjectReference();

	StorageObject();
}

OpFactory::~OpFactory()
{
	m_objects.clear();
}

void OpFactory::CreateObject()
{
	m_object = std::make_shared<Object>();

	m_skyBox = std::make_shared<SkyBox>();

	m_butterfly = std::make_shared<Butterfly>();
	m_butterflyLoad = std::make_shared<ButterflyLoad>();

	m_mediator = std::make_shared<Mediator>();

	m_opCamera = std::make_shared<OpCamera>();

}

void OpFactory::SetObjectReference()
{
	m_mediator->SetButterfly(m_butterfly);

	m_butterfly->SetMediator(m_mediator);
	m_opCamera->SetMediator(m_mediator);
}

void OpFactory::StorageObject()
{
	m_objects.emplace_back(m_skyBox);
	m_objects.emplace_back(m_butterfly);

}
