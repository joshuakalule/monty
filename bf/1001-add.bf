>+++++ +++[<+++++ + > -]< # 48 (c0)
> # c1 reserve
>, # byte1 (c2)
<<[>>-<<-]>> # convert to num
<<>+++++ +++[<+++++ + > -]<>> # rewrite 48 (c0)
>, # byte2 (c3)
<<<[>>>-<<<-]>>> # convert to num
<<<>+++++ +++[<+++++ + > -]<>>> # rewirte 48 (c0)
<[>+<-]> # add c2 to c3
<<<[>>>+<<<-]>>> # convert to byte
. # print c3
