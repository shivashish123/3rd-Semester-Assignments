note
	description: "project4 application root class"
	date: "$Date$"
	revision: "$Revision$"

class
	APPLICATION

inherit
	ARGUMENTS_32

create
	make

feature

		n,flag2: INTEGER					-- n is dimension of MATRIX, flag2 is 1 if matrix in not invertible else 0
		inverse_array: ARRAY2[REAL_64] 		--Inverse Matrix of given matrix
		input_array: ARRAY2[REAL_64]        --INPUT MATRIX
		epsilon : REAL_64
	make

		local
			my_array: ARRAY2[REAL_64]
			i,j : INTEGER
		do
			 io.read_integer
			 n := io.last_integer
			 create my_array.make (n,n)
			 create inverse_array.make (n,n)
			 create input_array.make (n,n)
			 from
			 	i:=1
			 until
			 	i>n
			 loop
				from
					j:=1
				until
					j>n
				loop
					io.read_real
					my_array.put (io.last_real,i,j) --another copy of input matrix which gets modified to identity matrix in Gauss-Jordan
					input_array.put(my_array.item (i,j),i,j)
					if(i=j)
						then inverse_array.put(1,i,j)  --setting the diagonal elements to be 1 ,rest other elements 0
					else
						inverse_array.put(0,i,j)
					end
					j:=j+1
				end
				i:=i+1
			 end
			 inverse(my_array)
			 if(flag2=0)
			 then
			 from
			 	i:=1
			 until
			 	i>n
			 loop
			 	from
			 		j:=1
			 	until
			 		j>n
			 	loop
			 		print(inverse_array.item (i,j))
			 		print(" ")
			 		j:=j+1
			 	end
			 	print("%N")
			 	i:=i+1
			 end
			 else
			 	print("INVALID")
			 end
		end
feature
	inverse(my_array: ARRAY2[REAL_64])

	require   --Pre-conditions
		non_empty : not my_array.is_empty
		non_negative : n>0
	local
		i,j,k,flag : INTEGER
		pivot : REAL_64
		factor : REAL_64
	do
		flag2:=0
		from
			i:=1
		until
			i>n or flag2=1
		loop
				flag:=0
				if(my_array.item (i,i)=0)-- if pivot element is 0 then if row swap is possible then row is swapped with other row else set flag2:=1
				then
					from
						k:=i+1
					until
						k>n or flag=1
					loop
						if(my_array.item (k,i)/=0)
						then flag:=1
							myswap(my_array,k,i) --swaps element of two rows 'k' and 'i'
						end
						k:=k+1
					end
				end
				if(my_array.item (i,i)=0)
				then flag2:=1
				else
					pivot:=my_array.item (i,i)
					from
						j:=1
					until
						j>n
					loop   --divide every element in the row by pivot
						my_array.put((my_array.item(i,j)/pivot),i,j)
						inverse_array.put((inverse_array.item(i,j)/pivot),i,j)
						j:=j+1
					end
					from
						k:=1
					until
						k>n
					loop
						if(k/=i)
						then
							factor:=my_array.item(k,i)
							from
								j:=1
							until
								j>n
							loop			-- performing Gauss Jordan Elimination
								my_array.put((my_array.item(k,j)-factor*my_array.item(i,j)),k,j)
								inverse_array.put((inverse_array.item(k,j)-factor*inverse_array.item(i,j)),k,j)
								j:=j+1
							end
						end
						k:=k+1
					end
				end
				i:=i+1
			end
			ensure		-- Post-conditions
				product_matrix_inversematrix_identity : isinverse(input_array,inverse_array)=true --product of matrix A and Inverse Matrix A should be Identity Matrix
				product_matrix_inversematrix_identity : isinverse(inverse_array,input_array)=true -- product of Inverse matrix A and Matrix A should be Identity Matrix
			rescue
				print("INVALID")
	end

feature

	myswap(my_array : ARRAY2[REAL_64]; x,y: INTEGER)	--swaps all the elements of two rows 'i' and 'j'

	require   --Pre-conditions
		non_empty : not my_array.is_empty
		non_negative : n>0
		non_negative : x>0
		non_negative : y>0

	local
		i: INTEGER
		temp : REAL_64
	do
		from
			i:=1
		until
			i>n
		loop
			temp:=my_array.item (x,i)
			my_array.item (x,i):=my_array.item (y,i)
			my_array.item (y,i):=temp
			temp:=inverse_array.item (x,i)
			inverse_array.item (x,i):=inverse_array.item (y,i)
			inverse_array.item (y,i):=temp
			i:=i+1
		end
		rescue
		print("INVALID")
	end
feature
	isinverse(a,b : ARRAY2[REAL_64]) : BOOLEAN -- checks the product of two matrices , if it is Identity matrix then return true else false
	local
		c : ARRAY2[REAL_64]  -- 'c' Matrix holds the product of two matrices 'a' and 'b'
		i,j,k,flag: INTEGER
	do
		create c.make(n,n)
		epsilon:=0.01
		RESULT:=true
		if (flag2=0) then
		from
			i:=1
		until
			i>n
		loop
			from
				k:=1
			until
				k>n
			loop
				c.put(0, i,k)
				from
					j:=1
				until
					j>n
				loop
					c.put(c.item (i,k)+a.item(i,j)*b.item (j,k),i,k)
					j:=j+1
				end
				k:=k+1
			end
			i:=i+1
		end
		flag:=0
		from
			i:=1
		until
			i>n or flag=1
		loop
			from
				j:=1
			until
				j>n or flag=1
			loop
				if(i=j and flag=0 and ((c.item (i,j)-1).abs)>epsilon)
				then flag:=1
					 RESULT:=false
				else if(i/=j and flag=0 and ((c.item (i,j)).abs)>epsilon)
				then flag:=1
					 RESULT:=false
				end
				end
				j:=j+1
			end
			i:=i+1
		end
		end
	end
end
