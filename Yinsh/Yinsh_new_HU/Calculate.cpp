int Board::eval_five(int N,int b1,int a1,int a2,int a3,int a4,int a5,int b2,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,int x5,int y5)
    {
        int points[] = {b1,a1,a2,a3,a4,a5,b2};

        int result = 0;
        int weights[] = {0,1,2,5,13,30}; // 0 ,1,2,3,4,5 discs or rings or blanks
        
        int flag = -1;

        // for (int i = 0; i < 7; ++i)
        // {
        //     if ((points[i]== 2 || abs(points[i])==3)&& flag==-1 )
        //     {
        //         flag = i;
        //     }
        //     else if((points[i] ==2 || abs(points[i])==3)&& (not (i==6 && flag==0)))  // found 2nd ring // 
        //     {


        //         for (int j = flag; j < i; j++)  // not to be evaluated 
        //         {
        //             points[j] = 2;
        //         }
        //     }

        // }
        int disc=0;
        int other_disc=0;
        int ring=0;
        int blank=0;
        int other_ring=0;
        for (int i = 1; i < 6; ++i)
        {
            if (points[i]==-1) // comp disc
            {
                disc = disc+1;
            }
            else if (points[i]==-1) // comp disc
            {
                other_disc = other_disc+1;
            }
            else if (points[i]==-2) // comp ring
            {
                ring  = ring +1;
            }
            else if (points[i]==2) // comp ring
            {
                other_ring  = other_ring +1;
            }
            else if(points[i]==0){ blank = blank +1;} // blank
        }
        int my_disc_can_convert_by_other=0;
    
        if (disc == 4){

        }
        else if (disc == 3){
            
        }


        result = 10*weights[disc] +  3* weights[ring] + 1*weights[blank] ;





        return result;
    }