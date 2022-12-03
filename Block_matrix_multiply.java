package matrix_multithread;



// This class handles mutithread functionality using Runnable method and has block mutiplication algorithm
public class Block_matrix_multiply implements Runnable 
{
	
	private final double[][] result;
	private double[][] matrix1;
	private double[][] matrix2;
	private final int size;
	

	public  Block_matrix_multiply(double[][] result, double[][] matrix1, double[][] matrix2, int size) {
		this.result = result;
		this.matrix1 = matrix1;
		this.matrix2 = matrix2;
		this.size = size;
		//System.out.println(matrix2[0].length);
	    //System.out.println(matrix1[0].length);
	    //System.out.println(size);
	}

	@Override
	public void run() 
	{
	    int i = 0, j = 0, k = 0, jj = 0, kk = 0;
		float tmp;
		int block_size = 16;
		//int en = size * (n/size);
		for (jj = 0; jj < size; jj += block_size)
		{
			
			for (kk = 0; kk < size; kk += block_size)
			{
				for (i = 0; i < size; i++)
				{
					for (j = jj; j < ((jj + block_size)> size ? size : (jj + block_size)) ; j++)//
					{
						tmp = 0.0f;
						for (k = kk; k < ((kk + block_size) > size ? size : (kk + block_size)); k++)//
						{
							tmp += matrix1[i][k] * matrix2[k][j];
						}
						result[i][j] += tmp;
					}
				}
			}
		}
	}
}
		
		

