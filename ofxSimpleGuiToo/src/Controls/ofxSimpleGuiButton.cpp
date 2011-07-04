
#include "ofxSimpleGuiButton.h"

ofxSimpleGuiButton::ofxSimpleGuiButton(const ofxSimpleGuiButton& copy) : ofxSimpleGuiControl(copy)
{
	
	beToggle = copy.beToggle;
	currentValue = copy.currentValue;
	
	name = copy.name;
	
	cout << " ofxSimpleGuiButton copying " << upImage << " " << hoverImage << " " << downImage << " " << selectedImage << " " << endl;
	
}

ofxSimpleGuiButton& ofxSimpleGuiButton::operator = ( const ofxSimpleGuiButton&  rhs )
{
	if (this == &rhs)
        return *this;
	
	beToggle = rhs.beToggle;
	currentValue = rhs.currentValue;
	
	ofxSimpleGuiControl::operator=(rhs);
	
	cout << " ofxSimpleGuiButton = ing " << upImage << " " << hoverImage << " " << downImage << " " << selectedImage << " " << endl;
	
	return *this;
}

ofxSimpleGuiButton::ofxSimpleGuiButton(string name, bool &value, ofImage* up, ofImage* down, ofImage* hover, ofImage* selected ) : ofxSimpleGuiControl(name) {
	beToggle	= false;
	beenPressed = false;
	currentValue = &value;
	controlType = "Button";
	isDown = false;
	isHovered = false;
	
	upImage = up;
	selectedImage = selected;
	downImage = down;
	hoverImage = hover;
	
	setup();
}

ofxSimpleGuiButton::ofxSimpleGuiButton(string name, bool &value) : ofxSimpleGuiControl(name) {
	beToggle	= false;
	beenPressed = false;
	currentValue = &value;
	controlType = "Button";
	isDown = false;
	isHovered = false;
	setup();
}

void ofxSimpleGuiButton::setup() {
	setSize(config->gridSize.x - config->padding.x, config->buttonHeight);
}

void ofxSimpleGuiButton::loadFromXML(ofxXmlSettings &XML) {
	setValue(XML.getValue(controlType + "_" + key + ":value", 0));
}

void ofxSimpleGuiButton::saveToXML(ofxXmlSettings &XML) {
	XML.addTag(controlType + "_" + key);
	XML.pushTag(controlType + "_" + key);
	XML.addValue("name", name);
	XML.addValue("value", getValue());
	XML.popTag();
}

void ofxSimpleGuiButton::keyPressed( int key ) {
	if(key==keyboardShortcut) toggle();
}

void ofxSimpleGuiButton::onRollOut ( ) {
	isDown = false;
	isHovered = false;
	
}

void ofxSimpleGuiButton::onRollOver ( int x, int y ) {
	
	isHovered = true;
	
}

bool ofxSimpleGuiButton::getValue() {
	return (*currentValue);
}

void ofxSimpleGuiButton::setValue(bool b) {
	(*currentValue) = b;
}

void ofxSimpleGuiButton::toggle() {
	(*currentValue) = !(*currentValue); 
}

void ofxSimpleGuiButton::setToggleMode(bool b) {
	beToggle = b;
}

void ofxSimpleGuiButton::onPress(int x, int y, int button) {
	beenPressed = true;	
	if(beToggle) (*currentValue) = !(*currentValue); 
	else (*currentValue) = true;
	
	isDown = true;
	cout << " is down " << isDown << endl;
}

void ofxSimpleGuiButton::onRelease(int x, int y, int button) {
	if(!beToggle) (*currentValue) = false;
	
	isDown = false;
}

void ofxSimpleGuiButton::draw(float x, float y) {
	setPos(x, y);
	
	glPushMatrix();
	glTranslatef(x, y, 0);

	// if a toggle
	if(currentValue && beToggle && !isHovered) {
		setTextColor();
		ofSetColor(255, 255, 255, 255);
		selectedImage->draw(0, 0);
		
	} else if ( hasHover && isHovered && !isDown ) {
		
		ofSetColor(255, 255, 255, 255);
		hoverImage->draw(0, 0);
		
	} else if ( isDown ) {
		
		if(hasDown) {
			ofSetColor(255, 255, 255, 255);
			downImage->draw( 0, 0 );
		}
		
	} else {
		if(hasUp)
		{
			ofSetColor(255, 255, 255, 255);
			upImage->draw(0, 0);
		}
		else
		{
			ofEnableAlphaBlending();
			ofFill();
			setTextBGColor();
			ofRect(0, 0, width, height);
		}
	}

	setTextColor();
	ofDrawBitmapString(name, 3, 15);
	
	ofDisableAlphaBlending();
	
	glPopMatrix();
}

bool ofxSimpleGuiButton::changed() {
	if(*currentValue != oldValue) {
		oldValue = *currentValue;
		return true;
	}
	return false;
}
