#pragma once

class Behaviour
{
public:
	virtual void OnEnable() {};
	virtual void OnDisable() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void OnDestroy() {};

	void SetEnabled(bool enable);
	bool GetEnabled() const;

	bool operator==(const Behaviour& other) const;

private:
	bool _enabled = true;
};
