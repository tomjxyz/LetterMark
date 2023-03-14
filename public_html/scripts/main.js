// Text area and output area variables
let ta, oa;

// Assign once page loaded
document.addEventListener('DOMContentLoaded', function (e) {
    ta = document.querySelector('textarea');
    oa = document.querySelector('.render');
});

// Handler for each keypress
function render() {
    oa.innerHTML = '';
    const source = ta.value.split('\n');
    for (line of source)
    {
        let plain = false;
        let elm;
        switch (line.substring(0, 3)) {
            case '.b ':
                elm = document.createElement('b');
                elm.innerText = line.substring(3);
                break;
            case '.i ':
                elm = document.createElement('i');
                elm.innerText = line.substring(3);
                break;
            case '.h ':
                elm = document.createElement('h1');
                elm.innerText = line.substring(3);
                break;
            case '.s ':
                elm = document.createElement('h3');
                elm.innerText = line.substring(3);
                break;
        
            default:
                plain = true;
                break;
        }
        if (plain)
        {
            if (line === "")
            {
                elm = document.createElement('p');
            }
            else 
            {
                elm = document.createElement('span');
                elm.innerText = line;
            }
        }
        oa.append(elm);
    }
}

document.addEventListener('keyup', render);