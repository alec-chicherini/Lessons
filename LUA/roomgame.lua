--small game to practice lua learning by book 
--"Programming in Lua" Third edition
--ROBERTO IERUSALIMSCHY
-- task 4.4



--generate random map
math.randomseed(os.time())
function rnd(x)
   
    y=math.random(1,x)
    return y
end

function printMap(map)
    for i=1,5 do
            print(map[(i-1)*5+1] .. map[(i-1)*5+2] .. map[(i-1)*5+3] .. map[(i-1)*5+4] .. map[(i-1)*5+5])
        end
end

--[[Converting from 2d map to one digit and vice verca

1  2  3  4  5
6  7  8  9  10
11 12 13 14 15
16 17 18 19 20
21 22 23 34 25

[x,y]
[1,3]  = 11
[5,5]  = 25
[3,4]  = 18

like that

]]
function XYtoSTR(X,Y)
    if X>5 or Y>5 or X<1 or Y<1 then print("Wrong X Y in XYtoSTR:" .. str) 
        else
        return 5*(Y-1)+X
    end
end

function STRtoXY(str)
    if str>25 or str<1 then print("Wrong str in STRtoXY:" .. str) end
    if str%5==0 then 
            x=5
            y=str//5
    else 
            x=str%5
            y=(str//5)+1 
        end
    return {["x"]=x,["y"]=y}
end

--[[
starting position:
000
010
000
]]
function generateMap() 
    map ={}
    for x=1,25 do map[x]='0' end
    --starting coord
    
    --random move in one of the direction
    --010
    --402
    --030

    STEP=3
    coord = { ["x"]=3, ["y"]=3 }--starting from center
    map[XYtoSTR(coord.x, coord.y)]='1'
    while(STEP>=1) do
        
        move=rnd(4)
        if move==1 then 
            if  coord.y-1>0 and map[XYtoSTR(coord.x, coord.y-1)]=='0'  then
                    coord.y=coord.y-1
                    map[XYtoSTR(coord.x, coord.y)]='1'
                    STEP=STEP-1
            end
        elseif move==2 then 
            if  coord.x+1<5 and map[XYtoSTR(coord.x+1, coord.y)]=='0'  then
                coord.x=coord.x+1
                map[XYtoSTR(coord.x, coord.y)]='1'
                STEP=STEP-1
            end
        elseif move==3 then 
            if  coord.y+1<5 and map[XYtoSTR(coord.x, coord.y+1)]=='0'  then
                coord.y=coord.y+1
                map[XYtoSTR(coord.x, coord.y)]='1'
                STEP=STEP-1
            end
        elseif move==4 then 
            if  coord.x-1>0 and map[XYtoSTR(coord.x-1, coord.y)]=='0'  then
                coord.x=coord.x-1
                map[XYtoSTR(coord.x, coord.y)]='1'
                STEP=STEP-1
            end
        end
    end
    return map
end

--main
map=generateMap()
copymap={}
for x=1,25 do copymap[x]=map[x] end


--printMap(MAP)
LIVES=3
STEP=3
print(" You are in the center of the room. Behind the three doors is death. In one way to exit.  ")
print(" You can move up, down, left or right. Cant go back. Exit out of the three doors.")

coord = { ["x"]=3, ["y"]=3 }--starting from center
while(true) do
    print("Lives = " .. LIVES)
    print("Where are u move?")
    input=io.read()
    if input == "up" then if coord.y-1>0 and map[XYtoSTR(coord.x, coord.y-1)]=='1' then
                     print("Good move! Whats next?")
                     map[XYtoSTR(coord.x, coord.y)]='0'
                     coord.y=coord.y-1
                     STEP=STEP-1
                    else
                     LIVES=LIVES-1
                    print("Wrong door.. sorry.. Lives = " .. LIVES)
                    coord.x=3
                    coord.y=3
                    STEP=3
                    for x=1,25 do map[x]=copymap[x] end
                     end
                    
    elseif input == "right" then if coord.x+1<6 and map[XYtoSTR(coord.x+1, coord.y)]=='1' then
                    print("You still alive! Whats next?")
                    map[XYtoSTR(coord.x, coord.y)]='0'
                    coord.x=coord.x+1
                    STEP=STEP-1
                    else
                     LIVES=LIVES-1
                     print("Bad move. Lives = " .. LIVES)
                     print("Returning to the first room...")
                     coord.x=3
                     coord.y=3
                     STEP=3
                     for x=1,25 do map[x]=copymap[x] end
                     end

    elseif input == "down" then if coord.y+1<6 and map[XYtoSTR(coord.x, coord.y+1)]=='1' then
                     map[XYtoSTR(coord.x, coord.y)]='0'
                    print("Good door! Whats next?")
                    coord.y=coord.y+1
                    STEP=STEP-1
                     else
                     LIVES=LIVES-1
                     print("Noooo.. Next time choose another. Lives = " .. LIVES)
                     print("Returning to the first room...")
                     coord.x=3
                     coord.y=3
                     STEP=3
                     for x=1,25 do map[x]=copymap[x] end
                    end

    elseif input == "left" then if coord.x-1>0 and map[XYtoSTR(coord.x-1, coord.y)]=='1' then
                    map[XYtoSTR(coord.x, coord.y)]='0'
                    print("Good move! Whats next?")
                    coord.x=coord.x-1
                    STEP=STEP-1
                     else
                     LIVES=LIVES-1
                    print("Not that way, you died. Lives = " .. LIVES)
                    print("Returning to the first room...")
                     coord.x=3
                    coord.y=3
                    STEP=3
                    for x=1,25 do map[x]=copymap[x] end
                     end

    elseif input == "map" then  printMap(map) 

    elseif input == "exit" then break 

    end
                    
if STEP==0 then 
        print("You win!")
        print("Lives = " .. LIVES)
        break
     end

if LIVES==0 then
        print("GAME OVER. New map generating...")
        LIVES=3
        map=generateMap()
        coord.x=3
        coord.y=3
        STEP=3
    end
    --printMap(map)
end


