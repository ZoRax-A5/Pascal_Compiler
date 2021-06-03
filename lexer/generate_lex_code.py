# # generate keyword code
# s = ''
# with open('Turbo_Pascal_keyword', 'r') as f:
#     s += f.read().upper()
# lst = s.split()

# # generate regex match code
# lst = []
# with open('temp', "r") as f:
#     while True:
#         s = f.readline()
#         if not s:
#             break
#         s = s.split()[0]
#         lst.append('{'+s+'} { return '+s+'; }')

# generate token
lst = []
with open('./data/substitution', 'r') as f:
    while True:
        s = f.readline()
        if not s:
            break
        s = s.split()[0]
        lst.append(s)

for idx, l in enumerate(lst):
    print(l, end=' ')
    if idx % 5 == 4:
        print()
