



    int evaluate_heuristic()
    {
        int weight_5 = 5;
        int weight_4 = 4;
        int weight_3 = 3;
        int weight_2 = 2;
        int weight_1 = 1;
        int weight_0 = 0;
        int result = 0;
        int b1 = -3 ; 
        int b2 = -3 ; 
        int max_X[] = {6,7,8,9,8,9,8,7,6};
        // Y = 0;
        for (int i = -4; i < 5; i++) // y axis
        {
            
            int y_m = max_X[i+4];
            for (int j = -y_m; j < y_m-8+1; j=j+2) // x-axis
            {   
                if (j== -y_m)
                {
                    b1 = -3;
                    b2 = temp_board_array[15+j+10][15+i];
                }
                else if (j== y_m - 8)
                {
                    b2 = -3;
                    b1 = temp_board_array[15+j-2][15+i];
                }
                else
                {
                    b1 = temp_board_array[15+j-2][15+i];
                    b2 = temp_board_array[15+j+10][15+i];   
                }
                result = result + eval_five(b1,temp_board_array[15+j][15+i],temp_board_array[15+j+2][15+i],temp_board_array[15+j+4][15+i],temp_board_array[15+j+6][15+i],temp_board_array[15+j+8][15+i],b2);
                result = result - eval_five(-b1,-temp_board_array[15+j][15+i],-temp_board_array[15+j+2][15+i],-temp_board_array[15+j+4][15+i],-temp_board_array[15+j+6][15+i],-temp_board_array[15+j+8][15+i],-b2);

            }
        }

        int y_cor[] = {-1,-2,-3,-4,-4,-5,-5,-5,-5} ; 
        int x_cor[] = {-9,-8,-7,-6,-4,-3,-1,1,3};
        int in_line[] = {2,3,4,5,4,5,4,3,2};
        int x = 0;
        int y = 0;
        int points_count = 0;
        
        // Y = X
        for (int i = 0; i < 9; ++i) 
        {
            x = x_cor[i];
            y = y_cor[i];
            while(true)
            {
                
                if (points_count==0)
                {
                    b1 = -3;
                    b2 = temp_board_array[15+x+5][15+y+5];
                }
                else if (points_count == in_line[i])
                {
                    b2 = -3;
                    b1 = temp_board_array[15+x-1][15+y-1];
                }
                else
                {
                    b1 = temp_board_array[15+x-1][15+y-1];
                    b2 = temp_board_array[15+x+5][15+y+5];
                }
                result = result + eval_five(b1,temp_board_array[15+x][15+y],temp_board_array[15+x+1][15+y+1],temp_board_array[15+x+2][15+y+2],temp_board_array[15+x+3][15+y+3],temp_board_array[15+x+4][15+y+4],b2);
                result = result - eval_five(-b1,-temp_board_array[15+x][15+y],-temp_board_array[15+x+1][15+y+1],-temp_board_array[15+x+2][15+y+2],-temp_board_array[15+x+3][15+y+3],-temp_board_array[15+x+4][15+y+4],-b2);
                x = x+1;
                y = y+1;
                if (points_count==in_line[i])
                {
                    points_count=0;

                    break;
                }
                points_count = points_count +1; 
            }

        }

        //// Y = - X
        int y_cord[] = {-5,-5,-5,-5,-4,-4,-3,-2,-1};
        int x_cord[] = {-3,-1,1,3,4,6,7,8,9};
        points_count=0;
        
        for (int i = 0; i < 9; ++i)
        {
            x = x_cord[i];
            y = y_cord[i];
            while(true)
            {
                
                if (points_count==0)
                {
                    b1 = -3;
                    b2 = temp_board_array[15+x-5][15+y+5];
                }
                else if (points_count == in_line[i])
                {
                    b2 = -3;
                    b1 = temp_board_array[15+x+1][15+y-1];
                }
                else
                {
                    b1 = temp_board_array[15+x+1][15+y-1];
                    b2 = temp_board_array[15+x-5][15+y+5];
                }
                result = result + eval_five(b1,temp_board_array[15+x][15+y],temp_board_array[15+x-1][15+y+1],temp_board_array[15+x-2][15+y+2],temp_board_array[15+x-3][15+y+3],temp_board_array[15+x-4][15+y+4],b2);
                result = result -eval_five(-b1,-temp_board_array[15+x][15+y],-temp_board_array[15+x-1][15+y+1],-temp_board_array[15+x-2][15+y+2],-temp_board_array[15+x-3][15+y+3],-temp_board_array[15+x-4][15+y+4],-b2);
                x = x-1;
                y = y+1;
                if (points_count==in_line[i])
                {
                    points_count=0;

                    break;
                }
                points_count = points_count +1;     
            }

        }
        

        return result;


    }