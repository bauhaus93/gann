#include <iostream>
#include <vector>


#include "NeuralNet.h"
#include "Drawer.h"
#include "Tests.h"

using namespace std;

static void PrintVector(vector<double>& vec, string title);
static void DrawNetwork(Drawer& drawer, NeuralNet& net, int startX, int startY, int width, int height);
extern bool RunTests(void);


int main(int argc, char **argv){

	NeuralNet nn(4, 4);
	nn.CreateRandom();
	vector<double> input = { 1, 2, 3, 4 };
	vector<double> output;

	nn.Simulate(input, output);
	PrintVector(input, "input: ");
	PrintVector(output, "output: ");


	Drawer d(1024, 768);
	DrawNetwork(d, nn, 100, 100, 500, 500);

	al_rest(3.0);

	return 0;
}

void DrawNetwork(Drawer& drawer, NeuralNet& net, int startX, int startY, int width, int height){

	float rectX = width / net.GetLayerCount();
	float rectY = height / net.GetLayerSize();
	float circleSize = min(rectX, rectY) * 0.3;


	drawer.SetColor(0, 0, 0);
	drawer.Clear();
	for (int i = 0; i < net.GetLayerCount(); i++){
		auto& layer = net[i];
		for (int j = 0; j < layer.GetNodeCount(); j++){
			auto& node = layer[j];
			int x = startX + i * rectX + rectX / 2;
			int y = startY + j * rectY + rectY / 2;

			
			for (int k = 0; k < node.GetConnectionCount(); k++){
				auto& conn = node[k];
				if (conn.IsActive()){
					if (conn.GetWeight() < 0)
						drawer.SetColor(0xFF, 0, 0);
					else
						drawer.SetColor(0, 0xFF, 0);
					drawer.Line(x, y, x + rectX, startY + k * rectY + rectY / 2);
				}
			}

			drawer.SetColor(0xFF, 0xFF, 0xFF);
			drawer.Circle(x, y, circleSize / 2, true);

		}
	}
	drawer.Rect(startX, startY, width, height);
	drawer.Flip();

}

void PrintVector(vector<double>& vec, string title){
	cout << title;
	for (int i = 0; i < vec.size(); i++){
		cout << vec[i];
		if (i + 1 == vec.size())
			cout << endl;
		else
			cout << "/";
	}
}