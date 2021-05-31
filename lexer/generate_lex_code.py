# generate keyword code
s = ''
with open('Turbo_Pascal_keyword') as f:
    s += f.read()
lst = s.split()

# generate regex match code
lst = []
with open('temp', "r") as f:
    while True:
        s = f.readline()
        if not s:
            break
        s = s.split()[0]
        lst.append('{'+s+'} { return '+s+'; }')

for l in lst:
    print(l)