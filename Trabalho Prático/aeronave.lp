\ENCODING=ISO-8859-1
\Problem name: IloCplex

Minimize
 obj: 1890000 x(Aviao0)(Voo0)#0 + 1452600 x(Aviao0)(Voo1)#1
      + 1452600 x(Aviao0)(Voo2)#2 + 1452600 x(Aviao0)(Voo3)#3
      + 1890000 x(Aviao0)(Voo4)#4 + 1610000 x(Aviao1)(Voo0)#5
      + 1237400 x(Aviao1)(Voo1)#6 + 1237400 x(Aviao1)(Voo2)#7
      + 1237400 x(Aviao1)(Voo3)#8 + 1610000 x(Aviao1)(Voo4)#9 + x15#14
Subject To
 Restricao_2(Voo0).#0:           x(Aviao0)(Voo0)#0 + x(Aviao1)(Voo0)#5  = 1
 Restricao_2(Voo1).#1:           x(Aviao0)(Voo1)#1 + x(Aviao1)(Voo1)#6  = 1
 Restricao_2(Voo2).#2:           x(Aviao0)(Voo2)#2 + x(Aviao1)(Voo2)#7  = 1
 Restricao_2(Voo3).#3:           x(Aviao0)(Voo3)#3 + x(Aviao1)(Voo3)#8  = 1
 Restricao_2(Voo4).#4:           x(Aviao0)(Voo4)#4 + x(Aviao1)(Voo4)#9  = 1
 Restricao_3(Aviao0)(Dia0).#5:   700 x(Aviao0)(Voo0)#0 + 538 x(Aviao0)(Voo1)#1
                                 + 538 x(Aviao0)(Voo2)#2
                                 + 538 x(Aviao0)(Voo3)#3
                                 + 700 x(Aviao0)(Voo4)#4
                                 - RgRestricao_3(Aviao0)(Dia0).#5  = 0
 Restricao_3(Aviao1)(Dia0).#6:   700 x(Aviao1)(Voo0)#5 + 538 x(Aviao1)(Voo1)#6
                                 + 538 x(Aviao1)(Voo2)#7
                                 + 538 x(Aviao1)(Voo3)#8
                                 + 700 x(Aviao1)(Voo4)#9
                                 - RgRestricao_3(Aviao1)(Dia0).#6  = 0
 Restricao_4(Aviao0)(Dia0).#7:   y(Aviao0)(Aeroporto0)(Dia0)#10
                                 + y(Aviao0)(Aeroporto1)(Dia0)#11  = 1
 Restricao_4(Aviao1)(Dia0).#8:   y(Aviao1)(Aeroporto0)(Dia0)#12
                                 + y(Aviao1)(Aeroporto1)(Dia0)#13  = 1
 Restricao_6(Voo0).#9:           174 x(Aviao0)(Voo0)#0 + 118 x(Aviao1)(Voo0)#5
                                 >= 172
 Restricao_6(Voo1).#10:          174 x(Aviao0)(Voo1)#1 + 118 x(Aviao1)(Voo1)#6
                                 >= 118
 Restricao_6(Voo2).#11:          174 x(Aviao0)(Voo2)#2 + 118 x(Aviao1)(Voo2)#7
                                 >= 105
 Restricao_6(Voo3).#12:          174 x(Aviao0)(Voo3)#3 + 118 x(Aviao1)(Voo3)#8
                                 >= 174
 Restricao_6(Voo4).#13:          174 x(Aviao0)(Voo4)#4 + 118 x(Aviao1)(Voo4)#9
                                 >= 108
 Restricao_7(Aviao0)(Voo0).#14:  x(Aviao0)(Voo0)#0
                                 - RgRestricao_7(Aviao0)(Voo0).#14  = 0
 Restricao_7(Aviao0)(Voo1).#15:  x(Aviao0)(Voo1)#1
                                 - RgRestricao_7(Aviao0)(Voo1).#15  = 0
 Restricao_7(Aviao0)(Voo2).#16:  x(Aviao0)(Voo2)#2
                                 - RgRestricao_7(Aviao0)(Voo2).#16  = 0
 Restricao_7(Aviao0)(Voo3).#17:  x(Aviao0)(Voo3)#3
                                 - RgRestricao_7(Aviao0)(Voo3).#17  = 0
 Restricao_7(Aviao0)(Voo4).#18:  x(Aviao0)(Voo4)#4
                                 - RgRestricao_7(Aviao0)(Voo4).#18  = 0
 Restricao_7(Aviao1)(Voo0).#19:  x(Aviao1)(Voo0)#5
                                 - RgRestricao_7(Aviao1)(Voo0).#19  = 0
 Restricao_7(Aviao1)(Voo1).#20:  x(Aviao1)(Voo1)#6
                                 - RgRestricao_7(Aviao1)(Voo1).#20  = 0
 Restricao_7(Aviao1)(Voo2).#21:  x(Aviao1)(Voo2)#7
                                 - RgRestricao_7(Aviao1)(Voo2).#21  = 0
 Restricao_7(Aviao1)(Voo3).#22:  x(Aviao1)(Voo3)#8
                                 - RgRestricao_7(Aviao1)(Voo3).#22  = 0
 Restricao_7(Aviao1)(Voo4).#23:  x(Aviao1)(Voo4)#9
                                 - RgRestricao_7(Aviao1)(Voo4).#23  = 0
 Restricao_8(Aviao0)(Aero0)(Dia0).#24: y(Aviao0)(Aeroporto0)(Dia0)#10
                                 - RgRestricao_8(Aviao0)(Aero0)(Dia0).#24  = 0
 Restricao_8(Aviao0)(Aero1)(Dia0).#25: y(Aviao0)(Aeroporto1)(Dia0)#11
                                 - RgRestricao_8(Aviao0)(Aero1)(Dia0).#25  = 0
 Restricao_8(Aviao1)(Aero0)(Dia0).#26: y(Aviao1)(Aeroporto0)(Dia0)#12
                                 - RgRestricao_8(Aviao1)(Aero0)(Dia0).#26  = 0
 Restricao_8(Aviao1)(Aero1)(Dia0).#27: y(Aviao1)(Aeroporto1)(Dia0)#13
                                 - RgRestricao_8(Aviao1)(Aero1)(Dia0).#27  = 0
Bounds
 0 <= x(Aviao0)(Voo0)#0 <= 1
 0 <= x(Aviao0)(Voo1)#1 <= 1
 0 <= x(Aviao0)(Voo2)#2 <= 1
 0 <= x(Aviao0)(Voo3)#3 <= 1
 0 <= x(Aviao0)(Voo4)#4 <= 1
 0 <= x(Aviao1)(Voo0)#5 <= 1
 0 <= x(Aviao1)(Voo1)#6 <= 1
 0 <= x(Aviao1)(Voo2)#7 <= 1
 0 <= x(Aviao1)(Voo3)#8 <= 1
 0 <= x(Aviao1)(Voo4)#9 <= 1
 0 <= y(Aviao0)(Aeroporto0)(Dia0)#10 <= 1
 0 <= y(Aviao0)(Aeroporto1)(Dia0)#11 <= 1
 0 <= y(Aviao1)(Aeroporto0)(Dia0)#12 <= 1
 0 <= y(Aviao1)(Aeroporto1)(Dia0)#13 <= 1
      x15#14 = 0
 0 <= RgRestricao_3(Aviao0)(Dia0).#5 <= 19920
 0 <= RgRestricao_3(Aviao1)(Dia0).#6 <= 19920
 0 <= RgRestricao_7(Aviao0)(Voo0).#14 <= 1
 0 <= RgRestricao_7(Aviao0)(Voo1).#15 <= 1
 0 <= RgRestricao_7(Aviao0)(Voo2).#16 <= 1
 0 <= RgRestricao_7(Aviao0)(Voo3).#17 <= 1
 0 <= RgRestricao_7(Aviao0)(Voo4).#18 <= 1
 0 <= RgRestricao_7(Aviao1)(Voo0).#19 <= 1
 0 <= RgRestricao_7(Aviao1)(Voo1).#20 <= 1
 0 <= RgRestricao_7(Aviao1)(Voo2).#21 <= 1
 0 <= RgRestricao_7(Aviao1)(Voo3).#22 <= 1
 0 <= RgRestricao_7(Aviao1)(Voo4).#23 <= 1
 0 <= RgRestricao_8(Aviao0)(Aero0)(Dia0).#24 <= 1
 0 <= RgRestricao_8(Aviao0)(Aero1)(Dia0).#25 <= 1
 0 <= RgRestricao_8(Aviao1)(Aero0)(Dia0).#26 <= 1
 0 <= RgRestricao_8(Aviao1)(Aero1)(Dia0).#27 <= 1
Binaries
 x(Aviao0)(Voo0)#0  x(Aviao0)(Voo1)#1  x(Aviao0)(Voo2)#2  x(Aviao0)(Voo3)#3 
 x(Aviao0)(Voo4)#4  x(Aviao1)(Voo0)#5  x(Aviao1)(Voo1)#6  x(Aviao1)(Voo2)#7 
 x(Aviao1)(Voo3)#8  x(Aviao1)(Voo4)#9  y(Aviao0)(Aeroporto0)(Dia0)#10 
 y(Aviao0)(Aeroporto1)(Dia0)#11  y(Aviao1)(Aeroporto0)(Dia0)#12 
 y(Aviao1)(Aeroporto1)(Dia0)#13 
End
