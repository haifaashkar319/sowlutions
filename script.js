const endpoint = 'https://api.manoapp.com/api/v1/users/products/whats_new';
const headers = {
    "StoreId": "4",
    "Authorization": "f44a4aabfc5992514d262d7f517327e7",
    "UserAddressID": "60877"
};
//I am aware of the security vulnerabilities of Javascript however
//implementing security measures in Javascript might be a bit challenging.
//I am not aware of measures I can implement here

fetch(endpoint, {
    method: 'GET',
    headers: headers
})
.then(blob => blob.json())
.then(data => {
    const items = data.data.items.map(item => ({
        title: item.title,
        price: item.price,
        category: item.categories[0].title, 
        quantity: item.quantity,
        image: item.images[0].thumbnail
    }));
//store items in items array
//I added the elemts you asked for to the items objects
    const itemsPerPage = 10;
    const paginationContainer = ".pagination-container";
    paginate(items, itemsPerPage, paginationContainer);
})
.catch(error => console.error('Error fetching data:', error));


function paginate(items, itemsPerPage, paginationContainer) {
    let currentPage = 1;
    const totalPages = Math.ceil(items.length / itemsPerPage);

    function showItems(page) {
        const startIndex = (page - 1) * itemsPerPage;
        const endIndex = startIndex + itemsPerPage;
        const pageItems = items.slice(startIndex, endIndex);

        const itemsContainer = document.querySelector('#items ul');
        itemsContainer.innerHTML = "";

        //populate items in pagination container
        pageItems.forEach((item) => {
            const li = document.createElement("li");
            li.innerHTML = item.title;
            //add and event listner so each item will show a pop up "modal" with more info about it
            li.addEventListener("click", () => {
                showModal(item);
            });
            itemsContainer.appendChild(li);
        });
    }

    function setupPagination() {
        const pagination = document.querySelector(paginationContainer);
        pagination.innerHTML = "";

        for (let i = 1; i <= totalPages; i++) {
            const link = document.createElement("a");
            link.href = "#";
            link.innerText = i;

            if (i === currentPage) {
                link.classList.add("active");
            }

            link.addEventListener("click", (event) => {
                event.preventDefault();
                currentPage = i;
                showItems(currentPage);

                const currentActive = pagination.querySelector(".active");
                if (currentActive) {
                    currentActive.classList.remove("active");
                }
                link.classList.add("active");
            });

            pagination.appendChild(link);
        }
    }

    showItems(currentPage);
    setupPagination();
}

function showModal(item) {
    const modalContent = document.querySelector('.modal-content');
    //add to the modal a close button 
    modalContent.innerHTML = `
        <span class="close-button" id="close-button" onclick="closeModal()">&times;</span>
        <p>Title: ${item.title}</p>
        <img src="${item.image}" alt="Movie Poster">
        <p>Price: ${item.price}</p>
        <p>Category: ${item.category}</p>
        <p>Quantity: ${item.quantity}</p>
     `;

    // Show the modal
    const modal = document.querySelector('.modal');
    modal.style.display = 'block';
}

function closeModal() {
    const modal = document.querySelector('.modal');
    modal.style.display = 'none';
}
