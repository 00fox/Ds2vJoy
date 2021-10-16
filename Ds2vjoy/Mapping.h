#pragma once
#include "DS.h"
#include "vJoy.h"

void MouseActions(int action, int delta = 0);
void MouseActionEnd(int action);

class Mapping
{
public:
	enum LedActionID {
		Led_Action_none,
		Led_Action_Led1,
		Led_Action_Led2,
		Led_Action_Led3,
		Led_Action_Led4,
		Led_Action_Led5,
		Led_Action_Battery,
		Led_Action_Count
	};

	enum MouseActionID {
		mouse_none,
		ACTIVE_MOUSE,
		MOVE_BACK,
		SAVE_POSITION,
		MOVE_TO_XY,
		MOVE_TO_WH,
		MOVE_TO_NN,
		SAVE_AND_MOVE_TO_XY,
		SAVE_AND_MOVE_TO_WH,
		SAVE_AND_MOVE_TO_NN,
		GRID_LEFT,
		GRID_UP,
		GRID_RIGHT,
		GRID_DOWN,
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
		MEMORIZE_MODE,
		TO_MODE1,
		TO_MODE2,
		TO_MODE3,
		TO_MODE4,
		TO_MODE5,
		TO_MODE6,
		TO_MODE7,
		TO_MODE8,
		TO_LAST_MODE,
		FORGOT_RELEASED,
		IF_RELEASED_GOTO,
		IF_PUSHED_GOTO,
		RETURN_TO,
		INTERRUPT,
		NO_SUSTAIN,
		PAUSE,
		mouse_Count
	};

	Mapping();
	~Mapping();

	const WCHAR* dsString();
	//First column is the principal source (see it particular function at the start of vJoy editing, and or/xor conditions)
	//Already configured vJoy buttons can be used as source, in conjunctions with DS buttons
	//'#' Indicates this button will be disabled for next mappings, except if 'Force' tag is activated (all)
	const WCHAR* dsLastString();
	//'+'  Indicates combination (second column)
	//'||' Indicates combination with or condition (second column)
	//'⊕'  Indicates combination with xor condition (second column)
	const WCHAR* dsNotString();
	//'-'  Indicates this mapping won't be launched if this button is pressed (see 'not' and 'pause' conditions) (third column)
	//'--' Indicates this mapping won't be launched if this button is pressed, but continue if already launched (third column)
	const WCHAR* vJoyString();
	//See a brief of what will be launched like vJoy, modes, mouse action (different from mouse)
	//'#' Indicates this button will be disabled for next mappings, when this button activated, except if 'Force' tag is activated
	//'>' Indicates this button will be disabled for next mappings, until the end of the time stamps, except if 'Force' tag is activated
	const WCHAR* NoticeString();
	//See a comment, notice, reminder, game rule, combo descritption, etc.
	//Takes palce instead of vJoyString(); by tape.MappingViewMode
	const WCHAR* TagsString();
	//| Tag | Description
	//|:--- |:------------------------------------------------------------------------------
	//|  I  | IfMouse condition is in use (see below)
	//|  F  | Force condition is in use (see below)
	//|  S  | Short press
	//|  D  | Double press (can be mixed, see below)
	//|  L  | Long press
	//|  C  | Macro condition is in use (see below)
	//|  P  | Pause condition is in use (see below)
	//|  Y  | Transitivity condition is in use (see below)
	//|  T  | Toggle condition is in use (see below)
	//| RZW | An OnRelease (/+NoRelease/+NlRelease) condition is in use (see below, under time stamps)
	//|  M  | If mouse will be in used (checkboxes choice, mouse actions are in vJoy Button) (see below)
	//a lowercase indicates that the checkbox is double checked for this condition
	const WCHAR* vJoyButtons();
	void PreLoad();
	BOOL LoadDevice(dsDevice*, vJoyDevice*);
	void RunFirst(vJoyDevice*);
	void RunLast(dsDevice*, vJoyDevice*);
	void Run(double average);
	static WCHAR* MouseString(MouseActionID id);
	static WCHAR* LedString(LedActionID id);

	unsigned char Enable;
	unsigned char Tab;
	unsigned char Ifmouse;		//1 if a mouse is already in use
								//2 if none mouse is actually in use
	unsigned char Force;		//1 to ignore if a button has been disabled by a precedent mapping
								//2 only if this mapping is already working
	bool Short;
	bool Double;
	bool Long;
	//| Checkboxes    | Method          | Description
	//|:------------- |:--------------- |:--------------------------------------------------
	//| None          | Simple          | Start when pressed, stop when release
	//| First         | Short*          | You have to press and release quickly
	//| Second        | Double          | You'll have to double press in a limited time
	//| Third         | Long            | You have to stay pressed from a certain time
	//| 1 & 2         | Double short(1) | Second press acting like short
	//| 2 & 2         | Double long     | Second press acting like long
	//| 1 & 3         | Medium long     | Like long but after double long
	//| All           | Very long       | 
	//
	//In terms of time:
	//| Method        | Press times
	//|:------------- |:--------------------------------------------------------------------
	//| Simple        | Immediate
	//| Short         | found in settings
	//| Double        | ~first press and second press < long
	//| Long          | found in settings
	//| Double        | ~first press and second press < long + second press duration < short
	//| Double short* | ~first press and second press < long + second press duration > long
	//| Medium long   | ~press > twice the time as long
	//| Very long     | found in settings
	unsigned char Led;
	unsigned char Macro;		//1 Macro: Interrupt macros on release (even if timestamp not finished),
								//2 No sustain: we use release value of first source instead of 0xFF if timestamp is still in use and we have released sources
	unsigned char Pause;		//1 pause this mapping while a not condition
								//otherwise if not is a simple, and not button is pressed, the mapping is interrupted
								//          if not is a double, and not button is pressed, the mapping still continue
								//2 One time, used in Transitivity
	unsigned char Transitivity;	//1 Transitivity: Principal way of transitivity which brings different behaviors and transition possibilities while mode changed
								//2 Come back, another way of transitivity which brings its owns (see table of transitivity below)
	//| Transitivity | Pause    | Type          | Result
	//|:------------ |:-------- |:------------- |: ------------------------------------------
	//| Transitivity |          | Complete      | You can release and trigger again in new mode
	//|              |          |               |if it was already active before changing mode
	//| Transitivity | One time | Limited       | Action continue while changing mode, but you can't trigger again if release
	//| Come back    |          | Retroactive   | Instead of continuation, button is released,
	//|              |          |               |but triggered again if still pushed when initial mode is back
	//| Come back    | One time | One time back | The same as Retroactive,
	//|              |          |               |but while pushed, you can change modeand get it triggered again only one time
	//|              |          |               |After, you have to releaseand trigger it again in its own mode
	//in any case, you cannot launch the mapping of a mode when another mode is active, if it was not activated before this change of mode
	unsigned char Toggle;		//1 satisfy mapping conditions one time to start, second one to stop
								//2 destinations states begin activated at program launch
	bool Target[5];
	byte dsID[5] = { dsButtonID::none };
	byte OrXorNot[4];
	//| OrXor1 | OrXor2 |     | Source1 |       | Source2 |       | Source3 |     |
	//|:------:|:------:|:---:|:-------:|:-----:|:-------:|:-----:|:-------:|:---:|
	//|   0    |   0    |     |   val   |   &   |   val   |   &   |   val   |     |
	//|  1/2   |   0    |  (  |   val   | OrXor |   val   |  ) &  |   val   |     |
	//|   0    |  1/2   |     |   val   |  & (  |   val   | OrXor |   val   |  )  |
	//|  1/2   |  …     |  (  |   val   | OrXor |   val   |   )   |         |  &  |
	//|  …     |  1/2   |  (  |   val   |       |         | OrXor |   val   |  )  |
	//
	//The source value used to calculate destination value is then:
	//| OrXor1 | OrXor2 | Source1 |     |     Released ?   |     | Source2 |     | Source3 |     | Source1 |
	//|:------:|:------:|:-------:|:---:|:----------------:|:---:|:-------:|:---:|:-------:|:---:|:-------:|
	//|   0    |   0    | val ? 0 |  >  |     Sustain ?    |     |         |     |         |  >  |released1|
	//|  1/2   |   0    | val ? 0 |  >  | 0xFF : released1 |  >  | val ? 0 |     |         |  >  |released1|
	//|   0    |  1/2   | val ? 0 |  >  |   (see Macro     |     |         |     |         |  >  |released1|
	//|  1/2   |  1/2   | val ? 0 |  >  |    condition)    |  >  | val ? 0 |  >  | val ? 0 |  >  |released1|
	//
	//1 The mapping won't be launched if this button is pressed
	//2 except if this mapping is already running
	//Taking into consideration that 'LastResult' is the result of the last or/xor table, the mapping is launched over those conditions:
	//| Not1 | Not2 | LastResult |       | Source4 |       | Source5 |
	//|:----:|:----:|:----------:|:-----:|:-------:|:-----:|:-------:|
	//|  0   |  0   |    val     |   &   |   val   |   &   |   val   |
	//|  1   |  0   |    val     | & Not |   val   |   &   |   val   |
	//|  0   |  1   |    val     |   &   |   val   | & Not |   val   |
	//|  1   |  1   |    val     | & Not |   val   | & Not |   val   |
	bool dsDisable[5];				//this button will be disabled for next mappings if this mapping is running (except with Force)
	unsigned char MouseAction[8];	//0 vJoy button, 1 Mouse, sound or mode action, 2 Axis movement
	unsigned char Overcontrol[8];	//0 axis of same type overpass precedent values, 1 values are merged, 2 if in use, next mapping won't interfer
	unsigned char Switch[8];		//Acts in conjunction with the toggle system, but act as a switch: 0 toggle (if Toggle active), 1 on, 2 off
	byte vjID[8] = { vJoyButtonID::none };
	unsigned char OnRelease[8];
	unsigned char NoRelease[8];		//1 no release while transitivity
									//2 do one turn when mode changed
	unsigned char NlRelease[8];		//0 NoRelease state for both if NoRelease active
									//1 normal release if back to initial mode
									//2 normal release while new mode
	unsigned char vjDisable[8];		//1 this button will be disabled for next mappings if this mapping is running (except with Force)
									//2 if time stamp is in use, disabling will be effective until whole mapping is finished instead this destination only
	unsigned char Mouse[7];			//0 left stick mouse type 0-5 (see below)
									//1 touchpad mouse type 0-5 (see below)
									//2 right stick mouse type 0-5 (see below)
									//3 disable this mosue for left stick
									//4 disable this mosue for touchpad
									//5 disable this mosue for right stick
									//6 for when you have together raid/grid and another mouse mode active, to determine which one is the default one
	//| Value | stick    | touchpad | Description (Table for Mouse[0-2])
	//|:-----:|:-------- |:-------- |:--------------------------------------------------------------------------------
	//| 0     | None     | None     |
	//| 1     | Absolute | Absolute | you move at a point which correspond to the coordinates of the stick or touchpad
	//| 2     | Mouse    | Mouse    | as a normal mouse with acceleration
	//| 3     | Move     | Slow     | the same but adapted for game movements, or precise mouse
	//| 4     | Sniper   | Accuracy | extreme precision
	//| 5     | Raid     | Grid     | move inside a zone whom coordinates are entered in numbers group at the right
	short Grid[6];					//0 x, 1 y, 2 w, 3 h, 4 nw, 5 nh
									//x and y define the starting point of the grid in which the mouse stay if you have activated grid mouse
									//w and h are the width and height of the grid
									//nw and nh are the number of columns abd row to which the mouse will stay docked, instead of free movement
									//if one or both is left to 0, free movement will be available for horizontal or vetical or both ways
									//
									//x, y and w, h can also be used to move the pointer to a location during special mouse action
	unsigned long Start[8];
	unsigned long Stop[8];
	WCHAR Notice[MAX_PATH];

private:
	dsButton* m_ds[5] = { 0 };
	vJoyButton* m_vj[13] = { 0 };
	unsigned char lastmode;				//Memorized mode stocked for this mapping only, when change to n(0-8, 0=Always) mode
	char tomode = -1;					//Destination mode stocked for this mapping only, when change to n(0-8, 0=Always) mode, available only for one turn, -1 after
	unsigned char locked;				//Different levels to trigger again when mode changed
	unsigned char modechanged;			//If mode has been changed by another mapping (mode<>tomode)
	unsigned char modedest[8];			//If mode has been changed by another mapping (mode<>tomode), one for each first eight destinations
	unsigned char modechangedto;		//Latest changed mode value
	bool legit = false;					//While pushing the good combination, method computing is eligible
	unsigned char method = 0;			//Actual method to check, ie double short step 1, short step 2 of double short, reinitialized after all done and new legit
	bool isFired = false;				//Computing the method is pending (short, double short etc.)
	bool available = false;				//First pass of the method is done, ie double for double short
	bool killed = false;				//This method is not eligible anymore, ie short can't be done if we already pushed the keys 250ms
	bool activated = false;				//Method has been done, and about to launch first step of actions
	bool isRunning = false;				//Actions are running still end of macros time or release
	unsigned long long cycle;			//number of cycles already done (used to pass as argument to mouse scroll actions)
	byte m_data;						//the value of m_ds[0]/m_vj[0]/0xFF(if none) to be used to fill, GetVal() if pushed, GetReleasedVal() else (simple or double)(0xFF else)
	bool Interrupttmp = false;			//temporary value, exactly alike to Macro=1, used with special time action 'Interrupt'
	bool NoSustain = false;				//temporary value, exactly alike to Macro=2, used with special time action 'No sustain'
	bool Pausetmp = false;				//temporary value, exactly alike to Pause=1, used with special time action 'Pause'
	bool released = false;				//Source of mapping has been released but actions still running, used to determine onReleae acts
	bool started[8] = { false };		//Individual start of each macro
	bool ran[8] = { false };			//If a macro has beeen processed at least one time
	bool done[8] = { false };			//If a macro is finished but other can still be contnuated or not
	bool MouseActiondone[8] = { false };//If a mouse action necessite am ending action, and this one has been done
	char TimeActiondone = -1;			//If a temporal action has to be done this turn in a decisional order, and which one, to perform only one, at the end of the turn
	bool GridCanbeUsed = false;			//If this mapping necessite one or several x,y,w,h values, or none (used to determine if we use grid values or not)
	bool Toggledone[8] = { false };		//If the toggle has been effectued for this macro for this run
	bool exists0 = false;				//If first source is defined
	bool exists1 = false;				//If second source is defined
	bool exists2 = false;				//If third source is defined
	bool pushed0 = false;				//If first source is pushed
	bool pushed1 = false;				//If second second is pushed
	bool pushed2 = false;				//If third source is pushed
	byte release0 = 0;					//Released value of first source
	bool killed0 = false;				//If first source is killed (like stay pushed more than tape.LongPress while method is short)
	bool killed1 = false;				//If second source is killed (then we have to wait for release to have a chance to try again)
	unsigned char secondpass = 0;		//If a source is killed but the second is activated, only with OrXorNot[0] && !OrXorNot[1] (except is second source available)
	byte OnReleaseValue = 0xFF;			//Used value when in On sustain mode (timestamp is sill in use and we have released all sources)
	std::chrono::system_clock::time_point start;		//start time (of computing method)
	std::chrono::system_clock::time_point end;			//actual time (of computing method)
	std::chrono::system_clock::time_point release;		//realease time (of computing method), for double, or wait before eligible again
	std::chrono::system_clock::time_point start2;		//start time (of running method)
	std::chrono::system_clock::time_point end2;			//actual time (of running method)
	std::chrono::system_clock::time_point release2;		//realeased time (when running method), to determine state of a macro and to launch onRelease actions
	std::chrono::milliseconds randStart[8] = { std::chrono::milliseconds(0) };	//repalce Start[8], and memorize + 0-9ms if Start[i] is odd
	std::chrono::milliseconds randStop[8] = { std::chrono::milliseconds(0) };	//replace Stop[8], and memorize + 0-9ms if Stop[i] is odd
};

static vJoyButton* m_vj_X;
static vJoyButton* m_vj_Y;
static vJoyButton* m_vj_Z;
static vJoyButton* m_vj_RX;
static vJoyButton* m_vj_RY;
static vJoyButton* m_vj_RZ;
static vJoyButton* m_vj_SL0;
static vJoyButton* m_vj_SL1;
extern unsigned char mode;										//Actual mode, shared by all mappings
static bool mouse_toggle[8] = { false };						//State of each possible 'Active mouse' toggle
static bool m_toggle[vJoyButtonID::button_Count] = { false };	//State of each individual vJoy button toggle
static std::vector<byte> dsDisabled;							//array of disabled dsButton to determine all nexts legit step
static std::vector<byte> vjDisabled;							//array of disabled vJoyButton to determine all nexts legit step
static std::vector<byte> vjUsed;								//memorize all vJoyButton used to release them at RunLast step of Ds2vJoy callback if necessary
static POINT movebackpoint = { 0, 0 };							//memorized mouse point, to move back in, in a futur possible action
static bool Ledactive[Mapping::Led_Action_Count] = { false };	//State of each individual Led

static WCHAR vJoyButtonsString[80];		//String of vJoy buttons in use, to show in status bar

static bool mouseactivated;				//mouse is running, used to determine legit if we use Ifmouse condition
extern unsigned char mousemode[3];		//[0]left axis, [1]touchpad, [2]right axis
										//0: deactivate, 1: absolute, 2: mouse, 3: move or slow, 4: sniper or accuracy, 5: raid or grid
extern unsigned char mouseabolute;		//Which one is absolute ([0]left axis, [1]touchpad or [2]right axis)(last one activated)
extern short grid[6];					//Grid to move cursor inside (x,y,w,h,nw,nh)
extern bool defaultmouse;				//false:all expept grid, true grid
extern std::vector<char> gridmove;		//movements to be done in a grid, with GRID_LEFT/UP/RIGHT/DOWN mouse actions

typedef std::vector<Mapping> Mappings;
typedef Mapping::MouseActionID MouseActionID;
typedef Mapping::LedActionID LedActionID;
