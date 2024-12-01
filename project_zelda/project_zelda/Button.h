#pragma once
#include "UI.h"

class Sprite;

enum ButtonState
{
	BS_Default,
	//BS_Hovered,
	BS_Pressed,
	BS_Clicked,
	// ...
	BS_MaxCount
};

class Button : public UI
{
	using Super = UI;
public:
	Button();
	virtual ~Button() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void	SetSize(Vec2Int size) { _size = size; }
	Sprite* GetSprite(ButtonState state) { return _sprites[state]; }

	void SetCurrentSprite(Sprite* sprite) { _currentSprite = sprite; }
	void SetSprite(Sprite* sprite, ButtonState state) { _sprites[state] = sprite; }
	void SetButtonState(ButtonState state);

protected:
	Sprite* _currentSprite = nullptr;
	Sprite* _sprites[BS_MaxCount] = {};
	ButtonState _state = BS_Default;
	// ...
	float _sumTime = 0.f;

public:
	template<typename T>
	void AddOnClickDelegate(T* owner, void(T::* func)())
	{
		_onClick = [owner, func]()
			{
				(owner->*func)();
			};
	}

	// void(int) Ÿ�� �ݹ� ���
	template<typename T>
	void AddOnClickDelegate(T* owner, void(T::* func)(int)) {
		_onClickWithInt = [owner, func](int value) {
			(owner->*func)(value);
			};
	}

	// �Լ� ������ + �Լ� ��ü
	std::function<void(void)> _onClick = nullptr;
	// void(int) �ݹ�
	std::function<void(int)> _onClickWithInt = nullptr;     // void(int) �ݹ�

public :
	int _selectedIndex = -1;
};

