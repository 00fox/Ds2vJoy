#pragma once
#include "DS.h"
#include "vJoy.h"

void MouseActions(int action, int delta = 0, int x = 0, int y = 0);
void MouseActionEnd(int action);

class Mapping
{
public:
	enum MouseActionID {
		none = 0,
		ACTIVE_MOUSE,
		SAVE_POSITION,
		MOVE_BACK,
		MOVE_TO_XY,
		MOVE_TO_WH,
		SAVE_AND_MOVE_TO_XY,
		SAVE_AND_MOVE_TO_WH,
		LEFT_CLICK,
		MIDDLE_CLICK,
		RIGHT_CLICK,
		X1_CLICK,
		X2_CLICK,
		SCROLL_UP,
		SCROLL_DOWN,
		LEFT_DOUBLE_CLICK,
		MIDDLE_DOUBLE_CLICK,
		RIGHT_DOUBLE_CLICK,
		X1_DOUBLE_CLICK,
		X2_DOUBLE_CLICK,
		SCROLL_UP_x5,
		SCROLL_DOWN_x5,
		LEFT_DOWN,
		MIDDLE_DOWN,
		RIGHT_DOWN,
		X1_DOWN,
		X2_DOWN,
		SCROLL_UP_VARIABLE,
		SCROLL_DOWN_VARIABLE,
		MUTE_SOUND,
		VOLUME_UP,
		VOLUME_DOWN,
		mouse_Count
	};

	Mapping();
	~Mapping();

	const WCHAR* dsString();
	const WCHAR* dsLastString();
	const WCHAR* dsNotString();
	const WCHAR* vJoyString();
	const WCHAR* TagsString();
	const WCHAR* vJoyButtons();
	void PreLoad();
	BOOL LoadDevice(dsDevice*, vJoyDevice*);
	void RunFirst();
	void RunLast(dsDevice* ds, vJoyDevice* vjoy);
	void Run();
	static WCHAR* String(MouseActionID id);

	bool Enable;
	dsButtonID dsID[5] = { dsButtonID::none };
	vJoyButtonID vjID[13] = { vJoyButtonID::none };
	bool Target[5];
	int Disable[13];
	int OrXorNot[4];
	int Ifmouse;
	int Force;
	int Led;
	bool Short;
	bool Double;
	bool Long;
	int Macro;
	bool Pause;
	int Toggle;
	int OnRelease[8];
	int Start[8];
	int Stop[8];
	int MouseAction[4];
	int Mouse[7];
	int Grid[6];

private:
	dsButton* m_ds[5] = { 0 };
	vJoyButton* m_vj[13] = { 0 };
	bool legit = false;					//While pushing the good combination, method computing is eligible
	int method = 0;						//Actual method to check, ie double short step 1, short step 2 of double short, reinitialized after all done and new legit
	bool isFired = false;				//Computing the method is pending (short, double short etc.)
	bool available = false;				//First pass of the method is done, ie double for double short
	bool killed = false;				//This method is not eligible anymore, ie short can't be done if we already pushed the keys 250ms
	bool activated = false;				//Method has been done, and about to launch first step of actions
	bool isRunning = false;				//Actions are running still end of macros time or release
	int cycle = 0;						//number of cycles already done (used to pass as argument to mouse scroll actions)
	BYTE m_data;						//the value of m_ds[0]/m_vj[0]/0xFF(if none) to be used to fill, GetVal() if pushed, GetReleasedVal() else (simple or double)(0xFF else)
	bool released = false;				//Source of mapping has been released but actions still running, used to determine onReleae acts
	bool started[8] = { false };		//Individual start of each macro
	bool ran[8] = { false };			//If a macro has beeen processed at least one time
	bool done[8] = { false };			//If a macro is finished but other can still be contnuated or not
	bool MouseActiondone[4] = { false };//If a mouse action necessite am ending action, and this one has been done
	bool GridCanbeUsed = false;			//If this mapping necessite one or several x,y,w,h values, or none (used to determine if we use grid values or not)
	bool Toggledone[8] = { false };		//If the toggle has been effectued for this macro for this run
	bool exists0 = false;		//If first source is defined
	bool exists1 = false;		//If second source is defined
	bool exists2 = false;		//If third source is defined
	bool pushed0 = false;		//If first source is pushed
	bool pushed1 = false;		//If second second is pushed
	bool pushed2 = false;		//If third source is pushed
	BYTE release0 = 0;			//Released value of first source
	bool killed0 = false;		//If first source is killed (like stay pushed more than tape.LongPress while method is short)
	bool killed1 = false;		//If second source is killed (then we have to wait for release to have a chance to try again)
	int secondpass = 0;			//If a source is killed but the second is activated, only with OrXorNot[0] && !OrXorNot[1] (except is second source available)
	BYTE OnReleaseValue = 0xFF;	//Used value when in On sustain mode (timestamp is sill in use and we have released all sources)
	std::chrono::system_clock::time_point start;	//start time (of computing method)
	std::chrono::system_clock::time_point end;		//actual time (of computing method)
	std::chrono::system_clock::time_point release;	//realease time (of computing method), for double, or wait before eligible again
	std::chrono::system_clock::time_point start2;	//start time (of running method)
	std::chrono::system_clock::time_point end2;		//actual time (of running method)
	std::chrono::system_clock::time_point release2;	//realeased time (when running method), to determine state of a macro and to launch onRelease actions
	std::chrono::milliseconds randStart[8] = { std::chrono::milliseconds(0) };	//repalce Start[8], and memorize + 0-9ms if Start[i] is odd
	std::chrono::milliseconds randStop[8] = { std::chrono::milliseconds(0) };	//replace Stop[8], and memorize + 0-9ms if Stop[i] is odd
	vJoyButtonID m_vjUsed;
};

static bool mouse_toggle[4] = { false };						//State of each possible 'Active mouse' toggle
static bool m_toggle[vJoyButtonID::button_Count] = { false };	//State of each individual vJoy button toggle
static std::vector<dsButtonID> dsDisabled;						//array of disabled dsButton to determine all nexts legit step
static std::vector<vJoyButtonID> vjDisabled;					//array of disabled vJoyButton to determine all nexts legit step
static std::vector<vJoyButtonID> vjUsed;						//memorize all vJoyButton used to release them at RunLast step of Ds2vJoy callback if necessary
static POINT movebackpoint = { 0, 0 };							//memorized mouse point, to move back in, in a futur possible action
static bool Ledactive[6] = { false };

static WCHAR vJoyButtonsString[80];

static bool mouseactivated;	//mouse is running, used to determine legit if we use Ifmouse condition
extern int mousemode[3];	//[0]left axis, [1]touchpad, [2]right axis
							//0: deactivate, 1: absolute, 2: mouse, 3: move or slow, 4: sniper or accuracy, 5: raid or grid
extern int mouseabolute;	//Which one is absolute ([0]left axis, [1]touchpad or [2]right axis)(last one activated)
extern int grid[6];			//Grid to move cursor inside (x,y,w,h,nw,nh)
extern bool defaultmouse;	//false:all expept grid, true grid

typedef std::vector<Mapping> Mappings;
typedef Mapping::MouseActionID MouseActionID;
