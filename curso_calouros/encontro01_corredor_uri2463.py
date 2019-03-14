
x = input()

corredor = list(map(int, input().split()))

"""
Solução inicial (lenta)
"""

def solve_slow2():
    maior = 0
    for i in range(len(corredor)):
        total = 0
        for j in range(i+1, len(corredor)):
            total += corredor[i]
        maior = max(maior, total)

"""
Solução do Kadane
"""

def solve_fast1():
    maior = corredor[0]
    mais_maior = corredor[0]
    for x in corredor[1:]:
        maior = max(x+maior, x)
        mais_maior = max(mais_maior, maior)
    return mais_maior

"""
Solução iterativa, convertida da recursiva
"""

def solve_fast2():
    results = [-1] * len(corredor)

    results[0] = corredor[0]

    for i in range(1, len(corredor)):
        results[i] = max(corredor[i], corredor[i] + results[i-1] )

    maior = 0
    for x in results:
        maior = max(maior, x)

    return maior


"""
Solução recursiva sem PD
"""
def solve_slow1(i):
    if i == len(corredor):
        return 0

    return max(corredor[i], corredor[i]+solve_slow1(i+1))


"""
Solução recursiva  com PD
"""
cache = [-1] * len(corredor)

def solve(i):
    if i == len(corredor):
        return 0

    if cache[i] != -1:
        return cache[i]

    cache[i] = max(corredor[i], corredor[i]+solve(i+1))
    return cache[i]


maior = 0
for i in range(len(corredor)):
    maior = max(maior, solve(i))

print(maior)
# print(solve_fast1())
# print(solve_fast2())
