#include "../[000]Object/[000]Stage/[000]SkyBox/SkyBox.h"
#include "../[000]Object/[001]Character/[003]Butterfly/Butterfly.h"
#include "../[000]Object/[001]Character/[003]Butterfly/[000]ButterflyFunction/ButterflyLoad.h"
#include "../[000]Object/[006]Title/Title.h"
#include "../[000]Object/[007]Gate/Gate.h"
#include "../[000]Object/[007]Gate/[000]GateFunction/GateLoad.h"
#include "../[000]Object/[008]OtherGraph/EnterGraph.h"
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

	m_title = std::make_shared<Title>();

	m_gate = std::make_shared<Gate>();
	m_gateLoad = std::make_shared<GateLoad>();

	m_enterGraph = std::make_shared<EnterGraph>();

	m_mediator = std::make_shared<Mediator>();

	m_opCamera = std::make_shared<OpCamera>();
}

void OpFactory::SetObjectReference()
{
	m_mediator->SetSkyBox(m_skyBox);
	m_mediator->SetButterfly(m_butterfly);
	m_mediator->SetButterflyLoad(m_butterflyLoad);
	m_mediator->SetTitle(m_title);
	m_mediator->SetGateLoad(m_gateLoad);
	m_mediator->SetEnterGraph(m_enterGraph);

	m_skyBox->SetMediator(m_mediator);
	m_butterfly->SetMediator(m_mediator);
	m_title->SetMediator(m_mediator);
	m_gate->SetMediator(m_mediator);
	m_opCamera->SetMediator(m_mediator);
}

void OpFactory::StorageObject()
{
	m_objects.emplace_back(m_skyBox);
	m_objects.emplace_back(m_gate);
	m_objects.emplace_back(m_butterfly);
	m_objects.emplace_back(m_title);
	m_objects.emplace_back(m_enterGraph);
}
