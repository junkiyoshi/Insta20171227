#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(30);
	ofBackground(255);
	ofSetWindowTitle("Insta");
	
	ofSetColor(0);
	ofFill();

	this->font.loadFont("Kazesawa-Bold.ttf", 150, true, false, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofTranslate(100, 50);

	char moji = 'A';
	for (int moji_index = 0; moji_index < 26; moji_index++) {

		ofTTFCharacter char_path = this->font.getCharacterAsPoints(moji);
		vector<ofPolyline> outline = char_path.getOutline();
		ofVec2f center;
		float noise_value;

		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index == 0) {
				center = outline[outline_index].getCentroid2D();
			}
			else {
				ofNextContour(true);
			}

			outline[outline_index] = outline[outline_index].getResampledByCount(300);

			vector<ofPoint> vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {
				ofPoint point = vertices[vertices_index] -center;
				noise_value = ofNoise(outline_index, point.x * 0.05, point.y * 0.05, ofGetFrameNum() * 0.05);
				if (noise_value < 0.5) {
					noise_value = 0.5;
				}
				ofVertex(point * noise_value);
			}
		}
		ofEndShape(true);

		if ((moji_index + 1) % 6 == 0) {
			ofTranslate(-500, 150);
		} else {
			ofTranslate(100, 0);
		}

		moji += 1;
	}
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
