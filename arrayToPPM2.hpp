#define INF 999999999
#include "cstdio"
#include "cstdlib"
#include "cstring"
#include "cmath"

#define linerFunc(x1,y1,x2,y2,x) ((x-x1)*(y2-y1)/(x2-x1)+y1)
#define linerFuncY(x1,y1,x2,y2,y) ((y-y1)*(x2-x1)/(y2-y1)+x1)

typedef double (*fun_P) (double);

typedef struct {
	int r, g, b;
} PPMdata;

template<class T>
void swap(T &a, T &b) {
	T c(a);
	a = b;
	b = c;
}

PPMdata makePPMdata(int r, int g, int b) {
	PPMdata ans;
	ans.r = r, ans.g = g, ans.b = b;
	return ans;
}

class Graph {
	private:
		PPMdata **matrix;
		int width;
		int height;
		double centerX;
		double centerY;
		double rangeX;
		double rangeY;
		double gridX;
		double gridY;
		PPMdata line, grid, bgc, axis;
		char *fileName;

		double stepX, stepY;
		bool drawed;
	public:
		Graph(int idth,
		      int eight,
		      double enterX,
		      double enterY,
		      double angeX,
		      double angeY,
		      double ridX,
		      double ridY,
		      PPMdata ine,
		      PPMdata rid,
		      PPMdata ack,
		      PPMdata xis,
		      char *fName);
		~Graph();
		bool drawLine(double x1, double x2, double y1, double y2);
		void drawPoint(double x, double y, int size);
		void drawPos(int u, int v, PPMdata color);
		bool drawXY(double *x, double *y, int arrayLen);
		int num2MatPos(double num, bool flag);
		void draw();
};

Graph::Graph(int idth,
             int eight,
             double enterX,
             double enterY,
             double angeX,
             double angeY,
             double ridX,
             double ridY,
             PPMdata ine,
             PPMdata rid,
             PPMdata ack,
             PPMdata xis,
             char *fName) {
	width = idth;
	height = eight;
	centerX = enterX;
	centerY = enterY;
	rangeX = angeX;
	rangeY = angeY;
	gridX = ridX;
	gridY = ridY;
	line = ine;
	grid = rid;
	bgc = ack;
	axis = xis;
	fileName = fName;
	drawed = 0;

	if (height % 2) ++height;
	if (width % 2) ++width;
	matrix = (PPMdata **) malloc(sizeof(PPMdata *) * height);
	for (int i = 0; i < height; i++) {
		matrix[i] = (PPMdata *) calloc(width, sizeof(PPMdata));
	}

	stepX = rangeX / (width * 1.0);
	stepY = rangeY / (height * 1.0);

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			matrix[i][j] = bgc;
		}
	}
	for (int i = 0; centerX + i * gridX <= centerX + rangeX / 2; ++i) {
		for (int j = 0; j < height; ++j) {
			drawPos(num2MatPos(centerX + i * gridX, 1), j, grid);
			drawPos(num2MatPos(centerX - i * gridX, 1), j, grid);
		}
	}
	for (int i = 0; centerY + i * gridY <= centerY + rangeY / 2; ++i) {
		for (int j = 0; j < width; ++j) {
			drawPos(j, num2MatPos(centerY + i * gridY, 0), grid);
			drawPos(j, num2MatPos(centerY - i * gridY, 0), grid);
		}
	}
	for (int i = 0; i < width; ++i) {
		drawPos(i, height / 2, axis);
	}

	for (int i = 0; i < height; ++i) {
		drawPos(width / 2, i, axis);
	}

}

Graph::~Graph() {
	if (drawed == 0) {
		draw();
	}
	fprintf(stderr, "Object has been deleted!\n");
}

void Graph::draw() {
	if (drawed) {
		fprintf(stderr, "This Graph has been drawed in %s.\n", fileName);
	}
	freopen(fileName, "w", stdout);
	printf("P3\n");
	printf("%d %d\n", width, height);
	printf("255\n");
	for (int i = height - 1; i >= 0 ; --i) {
		for (int j = 0; j < width; ++j) {
			printf("%d %d %d", matrix[i][j].r, matrix[i][j].g, matrix[i][j].b);
			printf(" ");
		}
		printf("\n");
	}
	fclose(stdout);
	freopen("CON", "w", stdout);
	drawed = 1;
}

int Graph::num2MatPos(double num, bool flag) {
	//flag=1 x else y
	if (flag) {
		return (int)(width / 2 + (num - centerX) / rangeX * width);
	} else {
		return (int)(height / 2 + (num - centerY) / rangeY * height);
	}
}

void Graph::drawPoint(double x, double y, int size) {
	int u = num2MatPos(x, 1);
	int v = num2MatPos(y, 0);
	for (int i = -1 * size; i <= size; ++i) {
		for (int j = -1 * size; j <= size; ++j) {
			int U = u + i, V = v + j;
			if (U >= width || U < 0 || V >= height || V < 0) continue;
			else matrix[V][U] = line;
		}
	}
}

void Graph::drawPos(int u, int v, PPMdata color) {
	if (u >= width || u < 0 || v >= height || v < 0) {
		return;
	} else matrix[v][u] = color;
}

bool Graph::drawLine(double x1, double y1, double x2, double y2) {
	int u1, u2, v1, v2;
	u1 = num2MatPos(x1, 1);
	u2 = num2MatPos(x2, 1);
	v1 = num2MatPos(y1, 0);
	v2 = num2MatPos(y2, 0);
	//fprintf(stderr, "%f %f %f %f \n", x1, y1, x2, y2);
	if (u1 >= width || u1 < 0 || u2 >= width || u2 < 0 || v1 >= height || v1 < 0 || v2 >= height || v2 < 0) {
		fprintf(stderr, "drawLineError:out of range.\n");
		return 0;
	}
	double k = INF;
	if (u2 != u1)
		k = (v2 * 1.0 - v1 * 1.0) / (u2 * 1.0 - u1 * 1.0);
	if (fabs(k) >= 2.0) {
		if (y1 > y2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		k=(x2-x1)/(y2-y1);
		double x11=x1;
		for (double y = y1; y <= y2; y += stepY) {
			drawPoint(x11, y, 1);
			x11+=stepY*k;
		}
	} else {
		if(x1>x2){
			swap(x1,x2);
			swap(y1,y2);
		}
		k=(y2-y1)/(x2-x1);
		double y11=y1;
		for (double x = x1; x <= x2; x += stepX) {
			drawPoint(x, y11, 1);
			y11+=stepX*k;
		}
	}
	//fprintf(stderr, "line cpc.\n");
	return 1;
}

bool Graph::drawXY(double *x, double *y_save, int arrayLen) {

	double *y = (double*)malloc(sizeof(double) * (arrayLen + 2));
	for (int i = 0; i < arrayLen; ++i)
		y[i] = y_save[i];
	for (int i = 0; i < arrayLen; ++i) {
		if (x[i] < x[i - 1] && i >= 1) {
			fprintf(stderr, "drawXYError:X is not increasing.\n");
			return 0;
		}
		if (!(x[i] > centerX - (rangeX / 2.0) && x[i] < centerX + (rangeX / 2.0))) {
			fprintf(stderr, "drawXYError:X out of range.\n");
			return 0;
		}
		if (!(y[i] > centerY - (rangeY / 2.0) && y[i] < centerY + (rangeY / 2.0))) {
			if (y[i] > centerY + (rangeY / 2.0)) y[i] = centerY + (rangeY / 2.0);
			if (y[i] < centerY - (rangeY / 2.0)) y[i] = centerY - (rangeY / 2.0);
		}
	}
	for (int i = 1; i < arrayLen; ++i) {
		if (i >= arrayLen) break;
		drawLine(x[i - 1], y[i - 1], x[i], y[i]);
	}
	free(y);
	return 1;
}
