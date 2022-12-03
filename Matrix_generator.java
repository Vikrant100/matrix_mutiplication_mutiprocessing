package matrix_multithread;

import java.util.Random;

// This class generates random matrix with given dimesions with random values
public class Matrix_generator 
{
	public static double[][] generateMatrix(int rows, int columns) {

		double[][] result = new double[rows][columns];

	
		Random random = new Random();
		
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {

				result[i][j] = random.nextInt(100) * 10;

			}
		}

		
		return result;
	}

	
}

