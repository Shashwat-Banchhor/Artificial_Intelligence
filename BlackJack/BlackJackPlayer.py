import random 

def get_val(l):
	val = sum(l)
	if (1 in l):
		if(val<=11):
			val += 10
	return val


def get_card(p,l):
	r = random.uniform(0,1)
	card = -1
	if (r<=p):
		card = 10
	else:
		card =  random.randint(1,9)
	l.append(card)
	return l

def Simulate_Dealer(p,card):  #  card is the max_val of the card  input after
	l = [card]
	l = get_card(p,l)
	is_BlackJack = 0
	if get_val(l)==21:
		is_BlackJack = 1
 	while True:
		if get_val(l)<17:
	 		l = get_card(p,l)
	 	if (get_val(l)>21):
	 		return [is_BlackJack,get_val(l)]
	 	if (get_val(l)>=17):
	 		break		
	return [is_BlackJack,get_val(l)]




def Cal_Terminal_prob(p,card):
	l = [0.0 for i in range(7)]				# [17,18,19,20,21,BlackJack,Bust]
	no_of_loops = 100000
	for i in xrange(1,no_of_loops):
		dealer_hand  = Simulate_Dealer(p,card)
		# ##print "Simulate_Dealer : " , dealer_hand
		dealer_BlackJack = dealer_hand[0]
		dealer_value = dealer_hand[1]
		if dealer_BlackJack==1 :
				l[5]+= 1
		else:
			# ##print "else"
			if dealer_value==17:
				l[0]+= 1
			elif dealer_value==18:
				l[1]+= 1
			elif dealer_value==19:
				l[2]+= 1
			elif dealer_value==20:
				l[3]+= 1
			elif dealer_value==21:
				l[4]+= 1
			elif dealer_value > 21:
				l[6]+= 1

    
	# for x in xrange(len(l)):
	# 	l[x] = l[x]/no_of_loops
	# #print ": ",sum(l),l,

	return l


# l = Cal_Terminal_prob(4.0/13,1)
# ##print l,sum(l)


def cal_Terminal_prob(p,card):  # [17,18,19,20,21,BlackJack,Bust]
	q = (1-p)/9

	bust = [0.0 for x in xrange(7)]
	BJ   = [0.0 for x in xrange(7)]
	hard = [[0.0 for x in xrange(7)]for x in range(22) ]
	soft = [[0.0 for x in xrange(7)]for x in range(17) ]
	pure = [[0.0 for x in xrange(7)]for x in range(11) ]

	# #print pure 
	# exit(0)
	bust[6] = 1.0
	BJ[5] = 1.0
	hard[21][4] = 1.0
	hard[20][3] = 1.0
	hard[19][2] = 1.0
	hard[18][1] = 1.0
	hard[17][0] = 1.0
	
	###### HARD TABLE ##########

	for x in xrange(16,10,-1):
		for i in xrange(1,10):
			if (x+i)<=21:
				hard[x] =  [ hard[x][j]+q*hard[x+i][j] for j in range(7)] #[q*a for a in hard[x+i]]
			else:
				hard[x] =  [ hard[x][j]+q*bust[j] for j in range(7)] #[q*a for a in bust]
	

	
		for i in xrange(10,11):
			if (x+i )<=21:
				hard[x] =  [ hard[x][j]+p*hard[x+i][j] for j in range(7)] #[p*a for a in hard[x+i]]
			else:
				hard[x] =  [ hard[x][j]+p*bust[j] for j in range(7)] #[p*a for a in bust]

	###### HARD TABLE ##########

	###### SOFT TABLE ##########

	for x in xrange(16,10,-1):
		for i in xrange(1,10):
			if (x+i)<=16:
				soft[x] =  [ soft[x][j]+q*soft[x+i][j] for j in range(7)] #[q*a for a in soft[x+i]]
			elif (x+i)<=21 :
				soft[x] = [ soft[x][j]+q*hard[x+i][j] for j in range(7)] #[q*a for a in hard[x+i]]
			else:
				soft[x] = [ soft[x][j]+q*hard[x+i-10][j] for j in range(7)] #[q*a for a in hard[x+i-10]]
	

	#for x in xrange(16,10,-1):
		for i in xrange(10,11):
			if (x+i)<=16:
				soft[x] = [ soft[x][j]+p*soft[x+i][j] for j in range(7)] #[p*a for a in soft[x+i]]
			elif (x+i)<=21 :
				soft[x] = [ soft[x][j]+p*hard[x+i][j] for j in range(7)] #[p*a for a in hard[x+i]]
			else:
				soft[x] = [ soft[x][j]+p*hard[x+i-10][j] for j in range(7)] #[p*a for a in hard[x+i-10]]
	
	###### SOFT TABLE ##########

	###### HARD TABLE  10 - 4##########
	for x in xrange(10,3,-1):
		for i in xrange(1,2):
			if x >= 6:
				hard[x] = [ hard[x][j]+q*hard[x+11][j] for j in range(7)] #[q*a for a in hard[x+11]]
			else:
				hard[x] = [ hard[x][j]+q*soft[x+11][j] for j in range(7)] #[q*a for a in soft[x+11]]

	#for x in xrange(10,3,-1):
		for i in xrange(2,10):
			hard[x] = [ hard[x][j]+q*hard[x+i][j] for j in range(7)] #[q*a for a in hard[x+i]]

	#for x in xrange(10,3,-1):
		for i in xrange(10,11):
			hard[x] = [ hard[x][j]+p*hard[x+i][j] for j in range(7)] #[p*a for a in hard[x+i]]

	###### HARD TABLE  10 - 4##########


	for x in xrange(10,1,-1):
		for i in xrange(1,2):
			if x==10:
				pure[x] = [ pure[x][j]+q*BJ[j] for j in range(7)] #[q*a for a in BJ]
			elif x+11>16:
				pure[x] = [ pure[x][j]+q*hard[x+11][j] for j in range(7)] #[q*a for a in hard[x+11]]
			else:	
				pure[x] = [ pure[x][j]+q*soft[x+11][j] for j in range(7)] #[q*a for a in soft[x+11]]

	#for x in xrange(10,1,-1):
		for i in xrange(2,10):
			pure[x] = [ pure[x][j]+q*hard[x+i][j] for j in range(7)] #[q*a for a in hard[x+i]]

	#for x in xrange(10,1,-1):
		for i in xrange(10,11):
			pure[x] = [ pure[x][j]+p*hard[x+i][j] for j in range(7)] #[p*a for a in hard[x+i]]


	for x in xrange(11,12): # Ace card
		for i in xrange(1,10):
			if (x+i)<17:	
				pure[x-10] = [ pure[x-10][j]+q*soft[x+i][j] for j in range(7)] #[q*a for a in soft[x+i]]
			else:
				pure[x-10] = [ pure[x-10][j]+q*hard[x+i][j] for j in range(7)] #[q*a for a in hard[x+i]]

	#for x in xrange(11,12): # Ace card
		for i in xrange(10,11):
			pure[x-10] = [ pure[x-10][j]+p*BJ[j] for j in range(7)] #[p*a for a in BJ]

	# for i in range(1,11):	
	# #print sum(pure[card]),pure[card]
	return pure[card]
			
			


def DoubleDownTransitionTable(p,q):
	l = [0 for i in range(111)] # intialization
	TransitionTable = [[0.0 for j in range(113)] for i in xrange(113)]  
	# index 0 is 5, 17 is 22, 26 is A10,  36 is AA ## Bust is [111] BJ is 112

	for state in xrange(0,5+1): # 5-10
		for k in xrange(state+2,state+9+1 ):
			TransitionTable[state][74+k] = q

		TransitionTable[state][74+state+11] = q
		TransitionTable[state][74 +state+10] = p


	for state in xrange(6,6+1):
		for k in xrange(state +1,state + 9+1):
			TransitionTable[state][74 +k] = q
		TransitionTable[state][74 +state+10] = p


	for state in xrange(7,14+1): #12-19
		for k in xrange(state+1,17):
			TransitionTable[state][74 +k] = q
		# 7 is 12, 8 is 13 , 15 is 20 
		TransitionTable[state][111]	= p + (state-7)*q	


	

	for state in xrange(18,25+1): # 18 is A2 and 26 is A10
		
		for k in xrange(state+1,26+1):
			
			TransitionTable[state][74+k] = q
		for k in xrange(7,state-10): 
			TransitionTable[state][74+k] = q
		
		TransitionTable[state][74+state-10] = p



	# 27 is 22 ,28 is 33, 35 is 1010,36 is AA
	
	k_start  = 1
	k_end    = 8
	ace_card = 20
	face_card = 9  
	for state in xrange(27,30+1):
		for k in xrange(k_start,k_end+1):
			TransitionTable[state][74+k] = q
		TransitionTable[state][74+ ace_card] = q
		TransitionTable[state][74+ face_card] = p
		k_start += 2 
		k_end += 2 
		ace_card +=2
		face_card +=2

	k_start  = 8
	k_end    = 16
	not_face_card = 0
	for state in xrange(31,35+1):  #(66,10
		for k in xrange(k_start,k_end+1):
			TransitionTable[state][74+k] = q
		TransitionTable[state][111] = p  + not_face_card*q

		k_start+=2
		not_face_card+=2

	for state in xrange(36,37):
		for k in xrange(18,26+1):
			TransitionTable[state][74+k] = q
		TransitionTable[state][74+7] = p

	return TransitionTable

def sPlitTransitionTable(p,q):
	# 27 is 22 ,28 is 33, 35 is 1010,36 is AA
	
	TransitionTable = [[0.0 for j in range(113)] for i in xrange(113)]  
	
	for state in xrange(27,35+1):
		k_start = state - 28  #
		for k in xrange(0,9):
			if k==0:
				TransitionTable[state][state - 27 + 18] = q
			else:
				if (k == state-26):
					TransitionTable[state][state]  = q
					k_start += 1
				else:
					TransitionTable[state][k_start]  = q
					k_start += 1

		if state==35:
			TransitionTable[state][state] = p
		else:
			TransitionTable[state][state-20]  = p

	for state in xrange(36,36+1):
		for k in xrange(0,9):
			if k==0:

				TransitionTable[state][74+state] = q
			else:
				TransitionTable[state][74+18+k-1] = q
		TransitionTable[state][74+26] = p


	return TransitionTable

def HitTransitionTable(p,q):
	l = [0 for i in range(111)] # intialization
	TransitionTable = [[0.0 for j in range(113)] for i in xrange(113)]  
	# index 0 is 5, 17 is 22, 26 is A10,  36 is AA ## Bust is [111] BJ is 112

	for state in xrange(0,5+1): # 5-10
		for k in xrange(state+2,state+9+1 ):
			TransitionTable[state][37+k] = q

		TransitionTable[state][37+state+21] = q
		TransitionTable[state][37 +state+10] = p


	for state in range(6,6+1):  # 11
		for k in xrange(state +1,state + 9+1):
			TransitionTable[state][37 +k] = q
		TransitionTable[state][37 +state+10] = p


	for state in xrange(7,14+1): #12-19
		for k in xrange(state+1,17):
			TransitionTable[state][37 +k] = q
		# 7 is 12, 8 is 13 , 15 is 20 
		TransitionTable[state][111]	= p + (state-7)*q	


	

	for state in xrange(18,25+1): # 18 is A2 and 26 is A10
		
		for k in xrange(state+1,26+1):
			
			TransitionTable[state][37+k] = q 
		for k in xrange(7,state-10): 
			TransitionTable[state][37+k] = q
		
		TransitionTable[state][37+state-10] = p



	# 27 is 22 ,28 is 33, 35 is 1010,36 is AA
	
	k_start  = 1 #6
	k_end    = 8 #13
	ace_card = 10 #15
	face_card = 9  #14
	for state in xrange(27,30+1):
		for k in xrange(k_start,k_end+1):
			TransitionTable[state][37+k] = q
		TransitionTable[state][37+ ace_card+10] = q
		TransitionTable[state][37+ face_card] = p
		k_start += 2 
		k_end += 2 
		ace_card +=2
		face_card +=2


	k_start  = 8 #13
	k_end    = 16 #21
	not_face_card = 0
	for state in xrange(31,35+1): #(66,1010)
		for k in xrange(k_start,k_end+1):
			TransitionTable[state][37+k] = q
		TransitionTable[state][111] = p  + not_face_card*q

		k_start+=2
		not_face_card+=2


	for state in xrange(36,37):
		for k in xrange(18,26+1): 
			TransitionTable[state][37+k] = q
		TransitionTable[state][37+7] = p


	####################################################################################

	for state in xrange(37+0,37+5+1): # 5-10
		for k in xrange(state-37+2,state-37+9+1 ):
			TransitionTable[state][37+k] = q

		TransitionTable[state][state+21] = q
		TransitionTable[state][state+10] = p


	for state in range(37+6,37+6+1):#== 37+6 :  # 11
		for k in xrange(state-37 +1,state-37 + 9+1):
			TransitionTable[state][37 +k] = q
		TransitionTable[state][state+10] = p


	for state in xrange(37+7,37+14+1): #12-19
		for k in xrange(state+1 -37,17):
			TransitionTable[state][37 +k] = q
		# 7 is 12, 8 is 13 , 15 is 20 
		TransitionTable[state][111]	= p + (state-37-7)*q	


	for state in range(37+15,37+15+1):# == 37+15 :  # 11
		
		TransitionTable[state][37+16] = q
		TransitionTable[state][111] = 1-(q)
		

	for state in xrange(37+18,37+25+1): # 18 is A2 and 26 is A10
		
		for k in xrange(state-37+1,26+1):
			
			TransitionTable[state][37+k] = q
		for k in xrange(7,state-37-10): 
			TransitionTable[state][37+k] = q
		
		TransitionTable[state][state-10] = p



	# 27 is 22 ,28 is 33, 35 is 1010,36 is AA
	
	# k_start  = 1 #6
	# k_end    = 8 #13
	# ace_card = 10 #15
	# face_card = 9  #14
	# for state in xrange(37+27,37+30+1):
	# 	for k in xrange(k_start,k_end+1):
	# 		TransitionTable[state][37+k] = q
	# 	TransitionTable[state][37+ ace_card+10] = q
	# 	TransitionTable[state][37+ face_card] = p
	# 	k_start += 2 
	# 	k_end += 2 
	# 	ace_card +=2
	# 	face_card +=2


	# k_start  = 8 #13
	# k_end    = 16 #21
	# not_face_card = 0
	# for state in xrange(37+31,37+35+1): #(66,1010)
	# 	for k in xrange(k_start,k_end+1):
	# 		TransitionTable[state][37+k] = q
	# 	TransitionTable[state][111] = p  + not_face_card*q

	# 	k_start+=2
	# 	not_face_card+=2


	# for state in xrange(37+36,37+37):
	# 	for k in xrange(18,26+1): 
	# 		TransitionTable[state][37+k] = q
	# 	TransitionTable[state][37+7] = p



	return TransitionTable

def StandTransitionTable(p,q):
	TransitionTable = [[0.0 for j in range(113)] for i in xrange(113)]  

	for state in xrange(0,37):
		if state ==26:
			TransitionTable[state][112]  = 1
		else:
			TransitionTable[state][state+74] = 1
	TransitionTable[15][15+74] = 0.0
	TransitionTable[16][16+7-4] = 0.0

	TransitionTable[17][17+74] = 0.0#007
	
	for state in xrange(37,74):
		TransitionTable[state][state+37] = 1

	return TransitionTable


def RewardTable(p,card):

	reward = [0 for x in xrange(113)]
 
 	
	l = cal_Terminal_prob(p,card) # [17,18,19,20,21,BlackJack,Bust]

	for state in range(0,36+1):
		if (state <12 or state in [18,19,20,21,27,28,29,30,31,32,33,36]): # 17
			reward[state+74] = 1*l[-1] -1*(1-l[-1])
		elif(state in [12,22]): #17
			reward[state+74] = 1*l[-1] -1*(1-l[-1]-l[0])
		elif(state in [13,23,34]): #18
			reward[state+74] = 1*(l[-1]+l[0]) -1*(1-l[-1]-l[0]-l[1])
		elif(state in [14,24]): #19
			reward[state+74] = 1*(l[-1]+l[0]+l[1]) -1*(1-l[-1]-l[0]-l[1]-l[2])
		elif(state in [15,25,35]): #20
			reward[state+74] = 1*(l[-1]+l[0]+l[1]+l[2]) -1*(1-l[-1]-l[0]-l[1]-l[2]-l[3])
		elif(state in [16,26]): #21
			reward[state+74] = 1*(l[-1]+l[0]+l[1]+l[2]+l[3]) -1*(1-l[-1]-l[0]-l[1]-l[2]-l[3]-l[4])

	reward[111] = -1  # irrespective of the dealers hand
	reward[112] = 1.5*(1-l[5]) #2.5 times return 

	return reward


def cal_split_reward(state,S_Table,R_Table,V_old):
	val = 0.0
	for state_dash in xrange(113):
		for state_double_dash in xrange(113):
			val +=  S_Table[state][state_dash]*S_Table[state][state_double_dash]*(R_Table[state_dash]+R_Table[state_double_dash]+V_old[state_dash]+V_old[state_double_dash])
	return val

def BlackJackPlayer(p): # 0-> H ,1 -> D , 2 -> S, 3 -> P
	q = float((1-p)/9)

	##print 0
	D_Table = DoubleDownTransitionTable(p,q)
	##print 1
	P_Table = sPlitTransitionTable(p,q)
	##print 2
	S_Table = StandTransitionTable(p,q)
	##print 3
	H_Table = HitTransitionTable(p,q)
	# for i in xrange(113):
	# 	#print P_Table[31][i] , i
	# exit(0)
	##print 4
	no_of_loops = 200
	epsilon = 0.000000001
	actions_store = [[0 for i in xrange(0,10)] for j in range(37)]
	
	for card in xrange(1,10+1):
		# #print 5
		R_Table = RewardTable(p,card)
		# #print R_Table
		# #print 6
		# exit(0)
		V_old = [0.0 for x in xrange(113)]
		V_new = [0.0 for x in xrange(113)]
		A_old = [-1 for x in xrange(113)]
		A_new = [-1 for x in xrange(113)]
		##print type(H_Table[1][0])
		##print type(R_Table[0])

		##print type(V_old[0])
		# exit(0)

		residual = 100

		n = 0
		while (residual > epsilon):#n<no_of_loops):# and residual > epsilon):
			
			V_old = V_new[:]
			A_old = A_new[:]
			
			

			for state in range(113):
				hit_val = 0
				double_down_val = 0
				split_val = 0
				stand_val = 0
				for state_dash in range(113):
					
					hit_val += H_Table[state][state_dash]*(R_Table[state_dash] + V_old[state_dash])
					double_down_val += D_Table[state][state_dash]*2*(R_Table[state_dash] + V_old[state_dash])
					split_val += P_Table[state][state_dash]*2*(R_Table[state_dash] + V_old[state_dash])
					stand_val += S_Table[state][state_dash]*(R_Table[state_dash] + V_old[state_dash])
				# if state == 26:
				# split_val += cal_split_reward(state,P_Table,R_Table,V_old) #P_Table[state][state_dash]*2*(R_Table[state_dash] + V_old[state_dash])
					
				action_val = [hit_val,double_down_val,stand_val,split_val]  # 0-> H ,1 -> D , 2 -> S, 3 -> P
				max_val = -200
				max_index = -5

				for i in xrange(0,4):
					if action_val[i]>max_val and action_val[i]!=0.0:
						max_val = action_val[i]
						max_index = i

				#print state,action_val

				if max_val==-200:
					V_new[state] = V_old[state]
				else:
					V_new[state] = max_val
				
				A_new[state] = max_index 

			# #print "V_new: ", V_new 
			# #print "V_old:  ", V_old
			V_diff = [abs(V_new[i]-V_old[i]) for i in xrange(113)]
			# #print V_diff
			# #print n
			residual = max(V_diff)
			n = n + 1
			#print card,n,"endo"
			# #print "Residual: ",residual
		for j in xrange(37):
			actions_store[j][card-1] = A_new[j]  # A is first

	
	actions_store_string = [["" for i in xrange(0,10)] for j in range(37)]
	for j in xrange(37):
		for i in xrange(10):
			if actions_store[j][i] == 0:
				actions_store_string[j][i] = "H"
			elif actions_store[j][i] == 1:
 				actions_store_string[j][i] = "D"	
 			elif actions_store[j][i] == 2:
 				actions_store_string[j][i] = "S"	

 			elif actions_store[j][i] == 3:
 				actions_store_string[j][i] = "P"

		
	possible_hands = ["5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","A2","A3","A4","A5","A6","A7","A8","A9","A10","22","33","44","55","66","77","88","99","1010","AA"]	
	hand = 0
	for i in xrange(0,15):
		state_string =  possible_hands[hand] + "\t" 
		for j in xrange(1,10):
			state_string = state_string +  actions_store_string[i][j] + " " 
		state_string = state_string + actions_store_string[i][0]	# A was first
		hand+=1
		print state_string

	hand+=3

	for i in xrange(18,26):
		state_string =  possible_hands[hand] + "\t" 
		for j in xrange(1,10):
			state_string = state_string +  actions_store_string[i][j] + " " 
		state_string = state_string + actions_store_string[i][0]	# A was first
		hand+=1
		print state_string

	hand+=1

	for i in xrange(27,37):
		state_string =  possible_hands[hand] + "\t" 
		for j in xrange(1,10):
			state_string = state_string +  actions_store_string[i][j] + " " 
		state_string = state_string + actions_store_string[i][0]	# A was first
		hand+=1
		print state_string

		



# for x in xrange(1,11):
# 	#print x,"************************"
# 	cal_Terminal_prob(4.0/13,x)
# 	Cal_Terminal_prob(4.0/13,x)
# 	#print "************************"
BlackJackPlayer(0.05)



























