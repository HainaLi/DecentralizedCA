#host1 = "ec2-52-90-67-39.compute-1.amazonaws.com"
#host2 = "ec2-54-175-99-252.compute-1.amazonaws.com"
host1 = "--"
host2 = "localhost"
three = "ec2-34-207-71-60.compute-1.amazonaws.com"
five = "ec2-54-227-208-110.compute-1.amazonaws.com"
host2 = five #define host2
num_executions = 72 #num of simultaneous executions
mode = "yao" #yao or dualex

print "make REMOTE_HOST=" + host1
print "make REMOTE_HOST=" + host2
#nohup command </dev/null >results.log 2>&1 &
for j in range(2):
	if j == 0:
		remote_host = "--"
	else:
		remote_host = host2
	
	start_port = 1234

	for port_num in range(start_port, start_port+num_executions):
		#command += "nohup ./a.out " + str(port_num) + " " + remote_host + " </dev/null >>results.log 2>&1 & "
		command += "./a.out " + str(port_num) + " " + remote_host + " "+mode+" signCert & "

	if mode == "Dualex": 
		command += "\n"

print "\n"
print command
print "\n"