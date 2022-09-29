#pragma once

/* --------- DATA --------- */

struct Data {
	double input[2];
	double expected_output[64]; // Output nodes wanted
	char label[64];
};

/* --------- DATA SET --------- */

struct DataSet {
	int length;
	struct Data data_set[1024];
};
