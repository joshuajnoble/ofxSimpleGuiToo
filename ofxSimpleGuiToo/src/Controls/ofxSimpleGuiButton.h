#pragma once

#include "ofxSimpleGuiControl.h"

class ofxSimpleGuiButton : public ofxSimpleGuiControl {
public:
	bool			beToggle;
	bool			beenPressed;
	
	ofxSimpleGuiButton(string name, bool &value);
	ofxSimpleGuiButton(const ofxSimpleGuiButton& copy);
	ofxSimpleGuiButton& operator = ( const ofxSimpleGuiButton&  rhs );
	
	ofxSimpleGuiButton(string name, bool &value, ofImage* up, ofImage* down, ofImage* hover, ofImage* selected );
	
	void setup();
	
	void loadFromXML(ofxXmlSettings &XML);	
	void saveToXML(ofxXmlSettings &XML);
	void keyPressed( int key );

	bool getValue();
	void setValue(bool b);
	void toggle();
	
	void setToggleMode(bool b);
	
	void onPress(int x, int y, int button);
	void onRelease(int x, int y, int button);
	void onRollOver ( int x, int y );
	void onRollOut();
	void draw(float x, float y);
	
	bool changed();
	
protected:
	
	bool	*currentValue;
	bool	oldValue;
	
	bool isHovered;
	bool isDown;
	
};
