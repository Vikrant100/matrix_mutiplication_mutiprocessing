package matrix_multithread;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;



// This class handle the mutlcore functionalty and provide time taken to complete the task
public class MatrixMultiplicationParallel {

		public static void main(String[] args) {
			
			for(int dimension=200; dimension<=2000; dimension+=200)
			{
			long start = System.currentTimeMillis();

			double[][] matrixA = Matrix_generator.generateMatrix(dimension, dimension); // call the matrix generator class for matrix creation 
			double[][] matrixB = Matrix_generator.generateMatrix(dimension, dimension); // call the matrix generator class  for matrix creation 

			double[][] result = new double[dimension][dimension]; // variable to store multiplication results.
			ExecutorService executor = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());// use of excutor for muticore functionality.
			//for(int i = 0; i < dimension; i++) {
			executor.execute(new Block_matrix_multiply(matrixA, matrixB, result, dimension));//}

			executor.shutdown();
			while(!executor.isTerminated()) 
			{}
			   
			//ParallelThreadsCreator.multiply(m1, m2, result);
			long end = System.currentTimeMillis();
			double elapsed = (end - start)/1000F;
			System.out.println("\nTime taken in seconds for dimension " + dimension+ "x" + dimension + " : "+  String.format("%.3f", elapsed) );
		}

	}
}

