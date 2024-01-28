#pragma once
#include "../Object.h"


class Title : public Object
{

public:

	Title();
	~Title();

private:

	
public:

	void Update(const float delta_time) override;

	void Draw(std::shared_ptr<GameCamera> gameCamera) override;



};
