package KnightsTour;

/**
 * @author Jared Cotton
 * @ID 125 089 185
 * @date April 13th, 2020
 * @subject BPT400 NAA
 */

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.FutureTask;

public class KnightsTourRandom {
	public static void main(String args[])
	{ 
		int tourResults[] = new int[65];
		boolean success = false;
		System.out.println("Running... (May take a few minutes)");
		
		while(!success)
		{
			@SuppressWarnings("unchecked")
			FutureTask<Integer>[] randomTours = new FutureTask[1000]; 
		  
			//run random tours 1000 at a time
		    for (int i = 0; i < randomTours.length; i++) 
		    { 
		      Callable<Integer> callable = new runRandomTour(); 
		  
		      randomTours[i] = new FutureTask<Integer>(callable); 

		      Thread t = new Thread(randomTours[i]); 
		      t.start(); 
		    } 
		    
		    //gather results from 1000 runs and see if any were successful
		    for (int i = 0; i < randomTours.length; i++) 
		    {  
			      try {
					tourResults[randomTours[i].get()]++;
					if(tourResults[64] == 1)
						{success = true;}
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (ExecutionException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} 
		    } 
		}
		
	    //Print results
	    System.out.println("Random Tours Results:");
	    for(int i = 0; i < tourResults.length; i++)
	    {
	    	if(tourResults[i] != 0) System.out.println(tourResults[i] + " tour(s) touched " + i + " squares.");
	    }
	    
	}
}
