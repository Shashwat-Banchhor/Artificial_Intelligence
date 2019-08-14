
######################################### XXXXXXX#########################################
#sample input
############
# k = 2
# p = 2
# t = 1
# C = 1
# Distances = [[0,0.4,0.8,1],[0.4,0,0.6,0.7],[0.8,0.6,0,0.3],[1,0.7,0.3,0]]
############
# Initialize
#Organization = [2,0,1,3]
#print Cost(Distances,Organization,k,p,t,C)
#while (time<deadline):
#exit(0)
######################################### Input #########################################
import sys
import time
import random 
t0 = time.time()
f = open(sys.argv[1], 'r')
o = open(sys.argv[2],'w')
deadline = (float(f.readline().rstrip()))*60
d0 =  min(1,deadline/(60*4))
k = int(f.readline().rstrip())
p = int(f.readline().rstrip())
t = int(f.readline().rstrip())
n = k*p*t
C = float(f.readline().rstrip())
Distances = []
def get_float(arr):
    temp = []
    for i in arr:
        temp.append(float(i))
    return temp
    
for i in range(n):
	temp = get_float(f.readline().rstrip().split(" "))
	Distances.append(temp)

######################################### XXXXXXX #########################################

#Compute_Cost
def Cost(Distances,Organization,k,p,t,C):
	# print "P: "+str(k) + "T: " + str(t) 
	similarity_index = 0
	for session in xrange(0,p*t):

			for paper1 in range(k-1):
				for paper2 in range(paper1+1,k):
					#print paper1#session*k+paper1
					#print paper2 ,session , k , session*k+paper2 , p*t
					#print "This is k" + str(k)
					similarity_index += (1- Distances[Organization[session*k+paper1]][Organization[session*k+paper2]])
					#print
				# print similarity_index
	# print "similarity_index : " +str(similarity_index)
	distance_index = 0
	
	for session1 in xrange(0,p*t-1):
		# print "yo" , session1
		for session2 in xrange(session1+1,p*t):
			# print "yo1" , session2
			if (session1/p != session2/p):
				break
			# 	print "NOoo"
			for index_p1 in range(k):
				# print "HI"
				for index_p2 in range(k):				
					# print "HI2"
					
					distance_index += Distances[Organization[session1*k+index_p1]][Organization[session2*k+index_p2]]
					# print distance_index

	# print "difference_index : " +str(distance_index)
	return (similarity_index + C*distance_index) 



def Cost_exchange(Distances,Organization,k,p,t,C,session1,session2 ,index_p1, index_p2,Cost_current):  # Just adds and subtracts the terms that are affected 
	Cost = 0																						   # Does not compute the whole cost again 
	if (session1/p !=session2/p):  # different time slots
		s1 = 0
		s2 = 0
		s1_new = 0
		s2_new = 0 
		for i in range(session1*k,index_p1):
			s1 = s1 + 1-Distances[Organization[i]][Organization[index_p1]]
		for i in range(index_p1+1,(session1+1)*(k)):	
			s1 = s1 + 1-Distances[Organization[i]][Organization[index_p1]]	

		for i in range(session2*k,index_p2):
			s2 = s2 + 1-Distances[Organization[i]][Organization[index_p2]]
		for i in range(index_p2+1,(session2+1)*(k)):	
			# print "--------------"
			# print len(Distances) , len(Distances[0])
			# print i , index_p2 , session2 , k
			# print Organization[i] , Organization[index_p2]
			s2 = s2 + 1-Distances[Organization[i]][Organization[index_p2]]	


		for i in range(session1*k,index_p1):
			s1_new = s1_new + 1-Distances[Organization[i]][Organization[index_p2]]
		for i in range(index_p1+1,(session1+1)*(k)):	
			s1_new = s1_new + 1-Distances[Organization[i]][Organization[index_p2]]		

		for i in range(session2*k,index_p2):
			s2_new = s2_new + 1-Distances[Organization[i]][Organization[index_p1]]
		for i in range(index_p2+1,(session2+1)*(k)):	
			s2_new = s2_new + 1-Distances[Organization[i]][Organization[index_p1]]	

		d1 = 0
		d2 = 0
		d1_new = 0
		d2_new = 0
		for session in range(session1-p,session1+p):
			if (session/p == session1/p):	
				if (session!= session1):
					for i in range(k):
						d1 = d1 + Distances[Organization[session*k + i]][Organization[index_p1]]
						d1_new = d1_new + Distances[Organization[session*k + i]][Organization[index_p2]]

		for session in range(session2-p,session2+p):
			if (session/p == session2/p):
				if (session!= session2):
					for i in range(k):
						d2 = d2 + Distances[Organization[session*k + i]][Organization[index_p2]]
						# print "d2" + str(Organization[session*k + i]) , str(Organization[index_p2])
						d2_new = d2_new + Distances[Organization[session*k + i]][Organization[index_p1]]

		# print s1,s2,s1_new,s2_new,d1,d2,d1_new,d2_new
		Cost = Cost_current -(s1+s2) + (s1_new+s2_new)+C*(-(d1+d2)+d1_new+d2_new)

	else:							# same time slots
		s1 = 0
		s2 = 0
		s1_new = 0
		s2_new = 0 
		d1 = 0
		d2 = 0
		d1_new = 0
		d2_new = 0
		for i in range(session1*k,index_p1):
			s1 = s1 + 1-Distances[Organization[i]][Organization[index_p1]]
			d1_new = d1_new + Distances[Organization[i]][Organization[index_p1]]
		for i in range(index_p1+1,(session1+1)*(k)):	
			s1 = s1 + 1-Distances[Organization[i]][Organization[index_p1]]	
			d1_new = d1_new + Distances[Organization[i]][Organization[index_p1]]

		for i in range(session2*k,index_p2):
			s2 = s2 + 1-Distances[Organization[i]][Organization[index_p2]]
			d2_new = d2_new + Distances[Organization[i]][Organization[index_p2]]
		for i in range(index_p2+1,(session2+1)*(k)):	
			s2 = s2 + 1-Distances[Organization[i]][Organization[index_p2]]	
			d2_new = d2_new + Distances[Organization[i]][Organization[index_p2]]
		for i in range(session1*k,index_p1):
			s1_new = s1_new + 1-Distances[Organization[i]][Organization[index_p2]]
			d1 = d1 + Distances[Organization[i]][Organization[index_p2]]
		for i in range(index_p1+1,(session1+1)*(k)):	
			s1_new = s1_new + 1-Distances[Organization[i]][Organization[index_p2]]
			d1 = d1 + Distances[Organization[i]][Organization[index_p2]]		

		for i in range(session2*k,index_p2):
			s2_new = s2_new + 1-Distances[Organization[i]][Organization[index_p1]]
			d2 = d2 + Distances[Organization[i]][Organization[index_p1]]
		for i in range(index_p2+1,(session2+1)*(k)):	
			s2_new = s2_new + 1-Distances[Organization[i]][Organization[index_p1]]	
			d2 = d2 + Distances[Organization[i]][Organization[index_p1]]
		
		Cost = Cost_current -(s1+s2) + (s1_new+s2_new)+C*(-(d1+d2)+d1_new+d2_new)
	return Cost
		

###########################

def output_string(Organization):
			s=""
			index = 0

			for j in range(t):
				for h in range(k-1):
						s =s+str(Organization[index])+ " "
						index+=1
				s =s+str(Organization[index])
				index+=1
				for i in range(p-1):
					s = s + "| "
					for h in range(k-1):
						s =s+str(Organization[index])+ " "
						index+=1
					s =s+str(Organization[index])
					index+=1
				s = s + "\n"
			return s
###########################


Organization = [i for i in range(n)]  # Generate a list of length l 

max_score = -1		# global max score
max_org = ""     	# the global maxima organization(string format)

while ((time.time())-t0 < deadline-d0):  # until dealine
	print "Hi"
	random.shuffle(Organization)		# shuffle the start list  #random restart
	
	while ((time.time())-t0 < deadline-d0): # until dealine
		
		max_good_neighbour =[]	     # best neighbour	
		max_good = 0				 # score of best neighbour
		Cost_current = Cost(Distances,Organization,k,p,t,C)
		Cost_current  = round(Cost_current,1)

		# print "Score: "+str(Cost_current) # + " Organization: "+ str(Organization) 
		for session1 in xrange(0,p*t-1):
			for session2 in xrange(session1+1,p*t):
				s1=0
				s2=0
				while(s1==s2):
						s1 = random.randrange(p*t-1)
						s2 = random.randrange(s1+1,p*t)

				for index_p1 in range(k):
					for index_p2 in range(k):
						neighbour = Organization[:]
						
						########### serialized neighbours
						# neighbour[session1*k+index_p1] = Organization[session2*k+index_p2]
						# neighbour[session2*k+index_p2] = Organization[session1*k+index_p1]
						
						# random neighbours
						# s1=0
						# s2=0
						# inp1 = 0
						# inp2 = 0
						# while(s1!=s2):
						# 	s1 = random.randrange(p*t-1)
						# 	s2 = random.randrange(s1+1,p*t)
						# 	inp1 = random.randrange(k)
						# 	inp2 = random.randrange(k)

						neighbour[s1*k + index_p1] = Organization[s2*k + index_p2]
						neighbour[s2*k + index_p2 ] = Organization[s1*k + index_p1]
						# print s1,s2
						#print  n , neighbour
						#n += 1
						# Cost_neighbour  = Cost(Distances,neighbour,k,p,t,C)
						# Cost_neighbour = Cost_exchange(Distances,Organization,k,p,t,C,session1,session2,session1*k+index_p1,session2*k+index_p2,Cost_current)
						
						Cost_neighbour = Cost_exchange(Distances,Organization,k,p,t,C,s1,s2,s1*k+index_p1,s2*k+index_p2,Cost_current)
						
						# Cost_neighbour = round(Cost_neighbour,1)
						# print "C,N"
						# print Cost_current,Cost_neighbour
						# print Organization , neighbour
						if (Cost_neighbour > Cost_current):
							
							max_good_neighbour = neighbour
							max_good  = Cost_neighbour
							
							Cost_current = max_good
							Organization = max_good_neighbour   # Update every time you find a greater neighbour
								
							print "Score0: "+str(max_good)  

						if ((time.time())-t0 > deadline-d0):   # write to the file and exit
								print "Yo"
								t2 =0 
								if (max_org==""):
									if (max_good_neighbour==[]):
										t2 = time.time()
										to_ret = output_string(Organization)
										o.write(to_ret)
										# print "time to write: " + str(time.time() - t2)
										print Cost_current ,0
									else:
										t2 = time.time()
										to_ret = output_string(max_good_neighbour)
										o.write(to_ret)
										# print "time to write: " + str(time.time() - t2)

										print max_good,1
									o.close()
									exit(0)
								else:
									# o.write(s)
									if (max_score > Cost_current):
										t2 = time.time()
										o.write(max_org)
										print max_score , 2
										o.close()
										# print "time to write: " + str(time.time() - t2)
									else:
										t2 = time.time()
										o.write(output_string(Organization))
										print Cost_current , 3
										o.close()
										# print "time to write: " + str(time.time() - t2)
									exit(0)

									

		if (max_good_neighbour != []):             #redundant 
				Organization = max_good_neighbour
				Cost_current = max_good
		else:
			break


		change_max  = False
		if  (max_score==-1):
			change_max = True
		else:
			if  (Cost_current > max_score):
	        		change_max = True
		if (change_max == True):	
			s=""
			index = 0

			for j in range(t):
				for h in range(k-1):
						s = s+str(Organization[index])+ " "
						index+=1
				s =s+str(Organization[index])
				index+=1
				for i in range(p-1):
					s = s + "| "
					for h in range(k-1):
						s =s+str(Organization[index])+ " "
						index+=1
					s =s+str(Organization[index])
					index+=1
				s = s + "\n"
			max_org = s
			max_score = Cost_current
		# print "######################################################################"
		# print (time.time())-t0 -(deadline-d0)
								
o.write(output_string(Organization))
o.close()
f.close()
exit(0)
