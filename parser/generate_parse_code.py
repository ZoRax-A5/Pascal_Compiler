lst = []
with open('./data/class_name', 'r') as f:
    while True:
        s = f.readline()
        if not s:
            break
        name = ''
        for i in s[3:]:
            if str.isupper(i):
                name += '_'+str.lower(i)
            else:
                name += i
        # print(s[:-1]+'* ast' + name[:-1]+';')
        lst.append('ast'+name[:-1])

for n in lst:
    print('%type<{}>'.format(n))