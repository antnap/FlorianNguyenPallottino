/*
 * input_controller.h
 *
 *  Created on: 25 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_INPUT_CONTROLLER_H_
#define DUAL_SIMPLEX_PROCEDURE_INPUT_CONTROLLER_H_


void input_controller(int argc, int source, int new_source, int n) {

	if (argc != 7) {

		 fprintf(stderr, "\n Incorrect input arguments! ");
		 fprintf(stderr, "\n The prototype of input is the following : \n");
		 fprintf(stderr, "\n ./exec_file <ARG1> <ARG2> <ARG3> <ARG4> <ARG5> ");
		 fprintf(stderr, "\n\n - where : ");
		 fprintf(stderr, "\n     ARG1 is an int that specifies the old_source");
		 fprintf(stderr, "\n     ARG2 is an int that specifies the new source");
		 fprintf(stderr, "\n     ARG3 is a string that specifies the instance path");
		 fprintf(stderr, "\n     ARG4 is a string that specifies the solution folder path");
		 fprintf(stderr, "\n     ARG5 is a string that specifies the time solution folder path\n\n");
		 fprintf(stderr, "\n     ARG6 is a string that specifies the file with the old solution\n\n");
		exit(-1);
	}

	if (source < 1 || source > n) {

		fprintf(stderr,
				"\n INVALID ARG1, a source must be included in the range [1, %d] \n\n",
				n);
		exit(-1);

	}
	if (new_source < 1 || new_source > n) {

		fprintf(stderr,
				"\n INVALID ARG2, a source must be included in the range [1, %d] \n\n",
				n);
		exit(-1);

	}
	if (new_source == source) {

		fprintf(stderr, "\n INVALID ARG2, it must be different from ARG1 \n\n");
		exit(-1);

	}

}


#endif /* DUAL_SIMPLEX_PROCEDURE_INPUT_CONTROLLER_H_ */
