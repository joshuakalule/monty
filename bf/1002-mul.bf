>+++++ +++[<+++++ + > -]< # 48 (c0)
> # reserve (c1)
>, # byte1 (c2)
<<[>+< >>-<<-]>> # set c1 to 48 AND convert byte1 to num
>, # byte2 (c3)
<<[<+> >>-<<-]>> # set c0 to 48 AND convert byte2 to num
< # (c2)
[<+> -] # copy c2 to reserve c1
>> # reserve (c4)
< # (c3)
[<+> >+< -] <<->> # copy c3 to c2 & c4 AND decrease c1 by 1
<< # (c1)
[>>> [<+> <<+>> -] <[>+<-]> <<< -] # add c4 to c2 c1 times while using (c4 & c3)
> # (c2)
<<[>>+<<-]>>. # print multiple