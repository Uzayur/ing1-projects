var=salut_bis

if echo ok; then
    echo ko
fi

echo salut
echo $var


var=5
while [ $var -gt 1 ]; do
    var=$(($var-1))
    echo $var
    break  5 
done
