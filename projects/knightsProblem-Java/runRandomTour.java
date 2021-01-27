package KnightsTour;

/**
 * @author Jared Cotton
 * @ID 125 089 185
 * @date April 13th, 2020
 * @subject BPT400 NAA
 */

import java.util.Random; 
import java.util.concurrent.Callable;
import javax.swing.*;
import javax.swing.border.Border;

import java.awt.*;
import java.util.ArrayList;

public class runRandomTour implements Callable<Integer> {
	//list of moves
	static final int[] horizontal = { 2, 1, -1, -2, -2, -1, 1, 2 };
	static final int[] vertical = { -1, -2, -2, -1, 1, 2, 2, 1 };
	
	/**
	 * @return int which is the number of squares which the tour has hit
	 */
	
	public Integer call() throws Exception{
		Random random = new Random();
		int[][] board = new int[8][8];
		Integer counter = 1;
		
		//knight row-column values
		int currentRow = random.nextInt(8);
		int currentColumn = random.nextInt(8);
		
		//set starting position to having been hit
		board[currentRow][currentColumn] = counter;
		
		boolean noMove = false;
		
		//outer loop that continues until no move is possible
		while(!noMove)
		{		
			ArrayList<Integer> possibleMoves = new ArrayList<Integer>();
			int move = -1;
			
			//inner loop that runs through each possible move, selecting one when a valid move is hit 
			for(int m = 0; m < 8; m++)
			{
				//valid when 'within board limits' and 'space not moved to before'
				if((currentRow + vertical[m]) < 8 && (currentRow + vertical[m]) >= 0 && 
						(currentColumn + horizontal[m]) < 8 && (currentColumn + horizontal[m]) >= 0 && 
						board[currentRow + vertical[m]][currentColumn + horizontal[m]] == 0){
					
						possibleMoves.add(m);
				}

			}
			
			if(possibleMoves.size() != 0)
			{
				move = possibleMoves.get(random.nextInt(possibleMoves.size()));
			}
			
			//after each possible move has been assessed
			if(move == -1)
			{
				noMove = true;
				
				if(counter == 64)
				{
					Frame frame = new JFrame("Tour Results");
					
					for(int i = 0; i < 8; i++)
					{
						for(int j = 0; j < 8; j++)
						{
							JLabel label = new JLabel(Integer.toString(board[i][j]));
							Border border = BorderFactory.createLineBorder(Color.black);
							label.setOpaque(true);
							label.setBackground(Color.yellow);
							label.setBorder(border);
							frame.add(label);
						}
					}
					
					frame.setLayout(new GridLayout(8,8));
					frame.setSize(300,300);
					frame.setVisible(true);
				}
			}
			else
			{
				currentRow += vertical[move];
				currentColumn += horizontal[move];
				++counter;
				board[currentRow][currentColumn] = counter;
			}
		}
			
			
		
		return counter;
	}
}
