#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);

	int radius = 15;
	for (float deg = 0; deg < 360; deg += 3) {

		auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		this->base_location_list.push_back(location);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->log_list.clear();

	int limit = 300;
	for (int i = 0; i < this->base_location_list.size(); i++) {

		vector<glm::vec2> log;
		log.push_back(glm::vec2(this->base_location_list[i]));
		this->log_list.push_back(log);
	}

	int step = 1;
	for (int i = 0; i < this->log_list.size(); i++) {

		int k = 0;
		while (true) {

			auto deg = ofMap(ofNoise(glm::vec3(this->log_list[i].back() * 0.003, ofGetFrameNum() * 0.006 + k * 0.0005)), 0, 1, -360, 360);
			auto next = this->log_list[i].back() + glm::vec2(step * cos(deg * DEG_TO_RAD), step * sin(deg * DEG_TO_RAD));

			if (next.x < -limit || next.x > limit || next.y < -limit || next.y > limit) {

				break;
			}
			else {

				this->log_list[i].push_back(next);
			}

			k++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofSetLineWidth(1.2);
	for (int i = 0; i < this->log_list.size(); i++) {

		if (this->log_list[i].size() > 1) {

			for (int k = 0; k < this->log_list[i].size(); k++) {

				ofSetColor(255, ofMap(k, 0, this->log_list[i].size(), 0, 255), ofMap(k, 0, this->log_list[i].size(), 0, 255));
				ofDrawCircle(this->log_list[i][k], 1);
			}
		}
	}

	ofNoFill();
	ofSetLineWidth(0.2);
	ofSetColor(255);
	ofDrawRectangle(-300, -300, 600, 600);

}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}