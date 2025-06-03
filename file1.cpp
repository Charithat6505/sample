<!-- Replace content between <nav> and <footer> -->
<div class="container my-5">
  <h2>Starters Menu</h2>
  <div class="row">
    <div class="col-md-4 menu-item">
      <h4>Chicken Wings</h4>
      <p>$5.99</p>
      <button class="btn btn-success" onclick="addToCart('Chicken Wings', 5.99)">Add to Cart</button>
    </div>
    <div class="col-md-4 menu-item">
      <h4>Spring Rolls</h4>
      <p>$3.99</p>
      <button class="btn btn-success" onclick="addToCart('Spring Rolls', 3.99)">Add to Cart</button>
    </div>
    <div class="col-md-4 menu-item">
      <h4>Garlic Bread</h4>
      <p>$2.99</p>
      <button class="btn btn-success" onclick="addToCart('Garlic Bread', 2.99)">Add to Cart</button>
    </div>
  </div>
</div>
<script src="cart.js"></script>
