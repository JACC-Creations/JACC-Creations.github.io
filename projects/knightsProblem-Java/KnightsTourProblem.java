package KnightsTour;

import java.awt.Color;
import java.awt.Frame;
import java.awt.GridLayout;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.border.Border;

/**
 * @author Jared Cotton
 * @ID 125 089 185
 * @date April 13th, 2020
 * @subject BPT400 NAA
 */

public class KnightsTourProblem {
	
	//list of moves
	static final int[] horizontal = { 2, 1, -1, -2, -2, -1, 1, 2 };
	static final int[] vertical = { -1, -2, -2, -1, 1, 2, 2, 1 };
	static int closedTours = 0;
	
	/**
	 * @param board This is the chess board which is an 8 by 8 two-dimensional array of type int
	 * @return returns new 8 by 8 array of each square in boards 'accessibility' rating
	 */
	
	static final public int[][] setAccessibility(int board[][]){
		
		int[][] accessibility = new int[8][8];
		
		for(int row = 0; row < 8; row++)
		{
			for(int column = 0; column < 8; column++)
			{
				for(int move = 0; move < 8; move ++) {
					if((row + vertical[move]) < 8 && (row + vertical[move]) >= 0 && 
							(column + horizontal[move]) < 8 && (column + horizontal[move]) >= 0 && 
							board[row + vertical[move]][column + horizontal[move]] == 0){
						accessibility[row][column]++;
					}
				}
			}
		}
		return accessibility;
	}
	
	/**
	 * @param board This is the chess board which is an 8 by 8 two-dimensional array of type int
	 * @param nextRow This is the row from which the nextMove is starting from
	 * @param nextColumn This is the column from which the nextMove is starting from
	 * @return int that is the lowest access rating from which this nextMove can reach
	 */
	
	static final public int checkNextMoveAccess(int board[][], int nextRow, int nextColumn)
	{
		int[][] accessibility = setAccessibility(board);
		int nextAccess = 100;
	
		//inner loop that runs through each possible move, selecting one when a valid move is hit 
		for(int m = 0; m < 8; m++)
		{
			//valid when 'within board limits' and 'space not moved to before'
			if((nextRow + vertical[m]) < 8 && (nextRow + vertical[m]) >= 0 && 
					(nextColumn + horizontal[m]) < 8 && (nextColumn + horizontal[m]) >= 0 && 
					board[nextRow + vertical[m]][nextColumn + horizontal[m]] == 0){
				//if move is valid, check its accessibility and if lower than other moves checked as of yet set to 'move'
				if(accessibility[nextRow + vertical[m]][nextColumn + horizontal[m]] < nextAccess)
				{
					nextAccess = accessibility[nextRow + vertical[m]][nextColumn + horizontal[m]];
				}
			}
		}
		
		return nextAccess;
	}
	
	/**
	 * @param startRow This is the row from which the tour starts
	 * @param startColumn This is the column from which the tour starts
	 * @return int which is the number of squares which the tour has hit
	 */
	
	static final public int runTour(int startRow, int startColumn){
		
		/// ***Part B***
				// arrays of type int are auto-initialized to zero
				int[][] board = new int[8][8];
				int[][] accessibility;
				
				//knight row-column values
				int currentRow = startRow;
				int currentColumn = startColumn;
				
				//counter to keep track of number of spots hit out of 64
				int counter = 1;
				
				//set starting position to having been hit
				board[currentRow][currentColumn] = counter;
				
				boolean noMove = false;
				
				//outer loop that continues until no move is possible
				while(!noMove)
				{		
					//holds chosen move
					int move = -1;
					int moveAccess = 100;
					
					//reset accessibility after each move made
					accessibility = setAccessibility(board);
					
					//inner loop that runs through each possible move, selecting one when a valid move is hit 
					for(int m = 0; m < 8; m++)
					{
						//valid when 'within board limits' and 'space not moved to before'
						if((currentRow + vertical[m]) < 8 && (currentRow + vertical[m]) >= 0 && 
								(currentColumn + horizontal[m]) < 8 && (currentColumn + horizontal[m]) >= 0 && 
								board[currentRow + vertical[m]][currentColumn + horizontal[m]] == 0){
							
							//if move is valid, check its accessibility and if lower than other moves checked as of yet set to 'move'
							if(accessibility[currentRow + vertical[m]][currentColumn + horizontal[m]] < moveAccess)
							{
								moveAccess = accessibility[currentRow + vertical[m]][currentColumn + horizontal[m]];
								move = m;
							}
							//comment this else if out if you want to see a failed result
							else if(accessibility[currentRow + vertical[m]][currentColumn + horizontal[m]] == moveAccess)
							{
								if(checkNextMoveAccess(board, currentRow + vertical[m], currentColumn + horizontal[m]) < checkNextMoveAccess(board, currentRow + vertical[move], currentColumn + horizontal[move]))
									move = m;
							}
						}
					}
					
					//after each possible move has been assessed
					if(move == -1)
					{
						noMove = true;
						if(counter != 64)
						{
							//code to output to console a board when failure
							Frame frame = new JFrame("Failed Tour Results");
							
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
						
						//check when full board tour complete if finishes within reach of starting position
						if(counter == 64)
						{
							//inner loop that runs through each possible move, selecting one when a valid move is hit 
							for(int m = 0; m < 8; m++)
							{
								//valid when 'within board limits' and 'space not moved to before'
								if((currentRow + vertical[m]) < 8 && (currentRow + vertical[m]) >= 0 && 
										(currentColumn + horizontal[m]) < 8 && (currentColumn + horizontal[m]) >= 0 && 
										board[currentRow + vertical[m]][currentColumn + horizontal[m]] == 0){
									if(board[currentRow + vertical[m]][currentColumn + horizontal[m]] == 1) closedTours++;
								}
							}
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
	
	public static void main(String args[])
	{
		int successfulTours = 0;
		
		for(int row = 0; row < 8; row++)
		{
			for(int column = 0; column < 8; column++)
			{
				if(runTour(row, column) == 64) successfulTours++;
			}
		}
		
		System.out.println("Number of successful tours: " + successfulTours);
		System.out.println("Number of closed tours: " + closedTours);
	}
}
