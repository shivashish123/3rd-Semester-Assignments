note
	description: "project3 application root class"
	date: "$Date$"
	revision: "$Revision$"

class
	APPLICATION

inherit
	ARGUMENTS_32
create
	make

feature

	n: INTEGER
	flag2 : INTEGER					--for invalid input
	m_array : ARRAY[INTEGER]		--Partner for every man
	w_array : ARRAY[INTEGER]		--Partner for every woman
	make
		local
			my_array: ARRAY2 [INTEGER]		-- preference table
			i,j,h: INTEGER
			x,y : REAL
		do
			 flag2:=0
			 io.read_integer
			 n := io.last_integer
			 create my_array.make (2*n,n)
			 from
			 	i:=1
			 invariant --loop invariant
				check_range : i>=1 and i<=2*n+1
			 until
			 	i>2*n
			 loop
			 	io.read_real
				x:=io.last_real
				if(i>n and x.rounded/=(i-n) and flag2=0)		--condition for valid input
					then flag2:=1
				else if(i<=n and x.rounded/=i and flag2=0)
					then flag2:=1
				end
				end
				from
					j:=1
				until
					j>n
				loop
					io.read_real
					y:=io.last_real
					h:=y.rounded
					if(h>n or h<1)
						then flag2:=1	--condition for valid input
					end
					my_array.put (h,i,j)
					j:=j+1
				end
				i:=i+1
			 end
			 stable_marriage(my_array)
			 rescue			-- If some precondition/postcondition/invariant fails, the program print “INVALID”
			 	print("INVALID")
		end
feature

	prefer(my_array : ARRAY2[INTEGER]; w,m1,m2 : INTEGER) : BOOLEAN -- if m1 is prefered more by w than m2 then return true else false
	local
		i : INTEGER
		flag : INTEGER
	do
		flag:=0
		from
			 i:=1
		invariant --loop invariant
			check_range : i>=1 and i<=n+1
	    until
			 i>n or flag=1
		loop
			if(my_array.item (w,i)=m1 and flag=0)	-- if m1 comes before m2 in preference row of w
				then flag:=1
					 RESULT:=true
			else if(my_array.item (w,i)=m2 and flag=0)-- if m2 comes before m1 in preference row of w
				then flag:=1
					RESULT:=false
		 	end
		 	end
		 i:=i+1
		 end
	end
feature

	stable_marriage(my_array : ARRAY2[INTEGER])	-- returns a stable matching
	require			-- Pre-conditions
			valid : n>0
			valid : flag2=0
			non_empty : not my_array.is_empty
			validinput : isvalid(my_array)=true		-- valid input
	local
		i,count,m1,m2,flag,woman : INTEGER
	do
		create m_array.make(1,n)
		create w_array.make(1,n)	-- creates array for partners of men and women
		from
			 i:=1
		invariant --loop invariant
			check_range : i>=1 and i<=n+1
	    until
			 i>n
		loop
			w_array.put(0,i)
			m_array.put (0, i)
			i:=i+1
		end
		from
			count:=n
		invariant --loop invariant
			check_range : count>=0 and count<=n
		until
			count=0
		loop
			flag:=0
			from
				i:=1
			invariant --loop invariant
				check_range : i>=1 and i<=n+1
			until
				i>n or flag=1
			loop
				if(m_array.item (i)=0 and flag=0)  -- get a free man(unmarried)
					then flag:=1
						 m1:=i
				end
				i:=i+1
			end
			from
				i:=1
			invariant --loop invariant
				checkstable : isstable(my_array)=true	-- checks if the matching till this iteration is stable or not
				check_range : i>=1 and i<=n+1
			until
				i>n or m_array.item (m1)>0
			loop
				woman := my_array.item (m1+n,i)
				if(w_array.item (woman)=0) -- if 'woman' is free then man 'm1' is engaged to 'woman'
					then w_array.put (m1,woman)
						 m_array.put (woman,m1)
						 count:=count-1
				else
					m2:=w_array.item (woman)	-- find current partner of 'woman',i.e. 'm2' and check the preference of 'woman'
					if(prefer(my_array,woman,m1,m2)=true) -- if 'm1' is preferred by 'woman' then her partner will be changed
					then w_array.put (m1,woman)
						m_array.put (woman,m1)
						m_array.put(0,m2)
					end
				end
				i:=i+1
			end
		end
		from
			i:=1
		invariant --loop invariant
				check_range : i>=1 and i<=n+1
		until
			i>n
		loop
			print(m_array.item (i))
			print("%N")
			i:=i+1
		end
		ensure  --	Post-condition
			checkstable : isstable(my_array)=true
		rescue
			print("INVALID")
	end
feature
	isvalid(my_array : ARRAY2[INTEGER]) : BOOLEAN --checks if the row of each man/woman contains permutation of {1,2...n}
	local
		check_array : ARRAY[INTEGER]
		i,j:INTEGER
		flag: INTEGER
	do
		RESULT:=true  -- if input is valid, return true else return false
		flag:=0
		create check_array.make(1,n)
		from
			i:=1
		until
			i>2*n or flag=1
		loop
			from
				j:=1
			until
				j>n
			loop
				check_array.put(0,j)
				j:=j+1
			end
			from
				j:=1
			until
				j>n or flag=1
			loop
				if(check_array.item(my_array.item (i, j))=1 and flag=0)
				then flag:=1
					 RESULT:=false
				else if(check_array.item(my_array.item (i, j))=0 and flag=0)
				then
					check_array.put(1,my_array.item (i,j))
				end
				end
				j:=j+1
			end
			i:=i+1
		end
	end

feature
	 isstable(my_array : ARRAY2[INTEGER]):BOOLEAN -- checks whether the matching is stable
	 local
	 	p,m,w,flag,i,j,k: INTEGER
	 do
	 	flag:=0
	 	RESULT:=true
	 	from
	 		i:=1
	 	until						-- iterating over all men
	 		i>n or flag=1
	 	loop
	 		p:=m_array.item(i)
	 		if(p/=0)				-- if partner of man 'i' is assigned then 'p' denotes his partner
	 		then
	 		from
				j:=1
	 		until
				j>n or my_array.item (i+n,j)=p or flag=1 -- checking the preference list of man 'i' before his partner 'p'
	 		loop
				w:=my_array.item (i+n,j)   -- denotes woman that comes before 'p' in preference list and 'm' is her partner
				m:=w_array.item (w)
				from
					k:=1
				until
					k>n or my_array.item (w,k)=m or flag=1 --check the preference list of woman 'w'
				loop
					if(my_array.item (w,k)=i)
					then flag:=1				-- if man 'm' comes after man 'i' then this won't be stable as 'i' can pair with 'w'
						 RESULT:=false			-- since both rather will have each other than their current partners
					end
					k:=k+1
				end
				j:=j+1
	 		end
	 		end
	 		i:=i+1
	 	end
	 end
end
