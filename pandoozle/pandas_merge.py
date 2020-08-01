#code credit: https://pandas.pydata.org/pandas-docs/stable/user_guide/merging.html
import pandas as pd

df1 = pd.DataFrame({'A': ['A0', 'A1', 'A2', 'A3'], 
                    'B': ['B0', 'B1', 'B2', 'B3'], 
                    'C': ['C0','C1','C2','C3'], 
                    'D': ['D0','D1','D2','D3'] },
                     index=[0,1,2,3])

print(df1)

df2 = pd.DataFrame({'B': ['B2', 'B3', 'B6', 'B7'],
                    'D': ['D2', 'D3', 'D6', 'D7'],
                    'F': ['F2','F3','F6','F7']},
                    index=[4, 5, 6, 7])

print(df2)
result = pd.concat([df1, df2], axis=1, sort=False)
print(result)

result = df1.append(df2, sort=False)
print(result)

a_df1 = pd.DataFrame([[1, 2], [3, 4]], columns=list('AB'))
a_df2 = pd.DataFrame([[5, 6], [7, 8]], columns=list('BC'))
result = a_df1.append(a_df2, ignore_index=True, sort=False)
print(result)
