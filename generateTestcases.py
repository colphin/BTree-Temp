nameList=[]
f = open("nameFile.txt","r");
lines = f.readlines();
for i in lines:
	nameList.append(i[:-3])
print len(set(nameList))
index = 0
insert = open("insertcode.txt", "w")
for name in nameList:
	insert.write("person {0};\n".format(name))
	insert.write("{0}.name=\"{0}\";\n".format(name))
	insert.write("{0}.index={1};\n".format(name,index))
	insert.write("t->insert({0});\n".format(name,index))
	insert.write("\n")
	index+=1